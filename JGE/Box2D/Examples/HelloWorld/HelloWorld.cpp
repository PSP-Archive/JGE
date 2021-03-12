/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Box2D.h"

#include <cstdio>

// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
int main(int argc, char** argv)
{
	NOT_USED(argc);
	NOT_USED(argv);

	// Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	b2AABB worldAABB;
	worldAABB.minVertex.Set(-100.0f, -100.0f);
	worldAABB.maxVertex.Set(100.0f, 100.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(worldAABB, gravity, doSleep);

	// Define the ground box shape.
	b2BoxDef groundBoxDef;

	// The extents are the half-widths of the box.
	groundBoxDef.extents.Set(50.0f, 10.0f);

	// Set the density of the ground box to zero. This will
	// make the ground body static (fixed).
	groundBoxDef.density = 0.0f;

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Part of a body's def is its list of shapes.
	groundBodyDef.AddShape(&groundBoxDef);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	world.CreateBody(&groundBodyDef);

	// Define another box shape for our dynamic body.
	b2BoxDef boxDef;
	boxDef.extents.Set(1.0f, 1.0f);

	// Set the box density to be non-zero, so it will be dynamic.
	boxDef.density = 1.0f;

	// Override the default friction.
	boxDef.friction = 0.3f;

	// Define the dynamic body. We set its position,
	// add the box shape, and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 4.0f);
	bodyDef.AddShape(&boxDef);
	b2Body* body = world.CreateBody(&bodyDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation. It is
		// generally best to keep the time step and iterations fixed.
		world.Step(timeStep, iterations);

		// Now print the position and rotation of the body.
		b2Vec2 position = body->GetOriginPosition();
		float32 rotation = body->GetRotation();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, rotation);
	}

	// When the world destructor is called, all memory is freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}

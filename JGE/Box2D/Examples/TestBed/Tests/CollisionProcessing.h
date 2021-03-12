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

#ifndef COLLISION_PROCESSING_H
#define COLLISION_PROCESSING_H

// This test shows collision processing and tests
// deferred body destruction.
class CollisionProcessing : public Test
{
public:
	CollisionProcessing()
	{
		// Ground body
		{
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(50.0f, 10.0f);
			sd.friction = 0.3f;

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		float32 xLo = -5.0f, xHi = 5.0f;
		float32 yLo = 2.0f, yHi = 35.0f;

		// Small triangle
		b2PolyDef triangleShapeDef;
		triangleShapeDef.vertexCount = 3;
		triangleShapeDef.vertices[0].Set(-1.0f, 0.0f);
		triangleShapeDef.vertices[1].Set(1.0f, 0.0f);
		triangleShapeDef.vertices[2].Set(0.0f, 2.0f);
		triangleShapeDef.density = 1.0f;

		b2BodyDef triangleBodyDef;
		triangleBodyDef.AddShape(&triangleShapeDef);
		triangleBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));

		m_world->CreateBody(&triangleBodyDef);

		// Large triangle (recycle definitions)
		triangleShapeDef.vertices[0] *= 2.0f;
		triangleShapeDef.vertices[1] *= 2.0f;
		triangleShapeDef.vertices[2] *= 2.0f;
		triangleBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));
		m_world->CreateBody(&triangleBodyDef);

		// Small box
		b2BoxDef boxShapeDef;
		boxShapeDef.extents.Set(1.0f, 0.5f);
		boxShapeDef.density = 1.0f;

		b2BodyDef boxBodyDef;
		boxBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));
		boxBodyDef.AddShape(&boxShapeDef);

		m_world->CreateBody(&boxBodyDef);

		// Large box (recycle definitions)
		boxShapeDef.extents *= 2.0f;
		boxBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));
		m_world->CreateBody(&boxBodyDef);

		// Small circle
		b2CircleDef circleShapeDef;
		circleShapeDef.radius = 1.0f;
		circleShapeDef.density = 1.0f;

		b2BodyDef circleBodyDef;
		circleBodyDef.AddShape(&circleShapeDef);
		circleBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));

		m_world->CreateBody(&circleBodyDef);

		// Large circle
		circleShapeDef.radius *= 2.0f;
		circleBodyDef.position.Set(b2Random(xLo, xHi), b2Random(yLo, yHi));
		m_world->CreateBody(&circleBodyDef);
	}

	void Step(const Settings* settings)
	{
		Test::Step(settings);

		// Traverse all the contacts in the world. Destroy bodies that
		// are touching heavier bodies.
		for (b2Contact* c = m_world->GetContactList(); c; c = c->GetNext())
		{
			// A positive manifold count ensures that the shapes are actually touching.
			if (c->GetManifoldCount() > 0)
			{
				b2Body* body1 = c->GetShape1()->GetBody();
				b2Body* body2 = c->GetShape2()->GetBody();
				float32 mass1 = body1->GetMass();
				float32 mass2 = body2->GetMass();

				if (mass1 > 0.0f && mass2 > 0.0f)
				{
					if (mass2 > mass1)
					{
						m_world->DestroyBody(body1);
						body1 = NULL;
					}
					else
					{
						m_world->DestroyBody(body2);
						body2 = NULL;
					}
				}
			}
		}
	}

	static Test* Create()
	{
		return new CollisionProcessing;
	}
};

#endif

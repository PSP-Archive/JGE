#include <JGE.h>
#include <JRenderer.h>
#include <JTypes.h>


#include "JBox2D.h"


JBox2D::JBox2D(float scale)
{
	b2AABB worldAABB;

	worldAABB.minVertex.Set(-120.0f, -100.0f);
	worldAABB.maxVertex.Set(120.0f, 160.0f);
	
	b2Vec2 gravity(0.0f, -10.0f);		// Define the gravity vector.
	bool doSleep = true;				// Do we want to let bodies sleep?

	// Construct a world object, which will hold and simulate the rigid bodies.
	mWorld = new b2World(worldAABB, gravity, doSleep);

	mTimer = 0.0f;

	mScale = scale;

}


JBox2D::~JBox2D()
{

}


void JBox2D::Update(float dt)
{
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 2;

	mTimer += dt;
	if (mTimer >= timeStep)
	{
		mTimer -= timeStep;
		
		// Instruct the world to perform a single step of simulation. It is
		// generally best to keep the time step and iterations fixed.
		mWorld->Step(timeStep, iterations);
	}

}


void JBox2D::Render()
{

	JRenderer* renderer = JRenderer::GetInstance();	

	float xx[32];
	float yy[32];

	for (b2Body* b = mWorld->m_bodyList; b; b = b->m_next)
	{

		for (b2Shape* shape = b->m_shapeList; shape; shape = shape->m_next)
		{


			switch (shape->m_type)
			{
			case e_circleShape:
				{
					const b2CircleShape* circle = (const b2CircleShape*)shape;
					b2Vec2 pos = circle->m_position;
					float32 r = circle->m_radius;

					renderer->DrawCircle(pos.x, pos.y, r, ARGB(255,255,255,255));
				}
				break;

			case e_polyShape:
				{
					const b2PolyShape* poly = (const b2PolyShape*)shape;

					for (int32 i = 0; i < poly->m_vertexCount; ++i)
					{
						b2Vec2 v = poly->m_position + b2Mul(poly->m_R, poly->m_vertices[i]);
						xx[i] = 240+v.x*mScale;
						yy[i] = 260-v.y*mScale;
					}

					renderer->DrawPolygon(xx, yy, poly->m_vertexCount, ARGB(255,255,255,255));

				}
				break;
			}
		}

	}

}

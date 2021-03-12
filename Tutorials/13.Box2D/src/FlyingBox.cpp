#include <JGE.h>
#include <JRenderer.h>
#include <JTypes.h>

#include "FlyingBox.h"


FlyingBox::FlyingBox():
	JBox2D(BOX_SCALING)
{
	mTexture = NULL;
	mQuad = NULL;
	mBodies = NULL;
}



FlyingBox::~FlyingBox()
{
	SAFE_DELETE(mTexture);
	SAFE_DELETE(mQuad);
	SAFE_DELETE_ARRAY(mBodies);

}


void FlyingBox::Create()
{
	mTexture = JRenderer::GetInstance()->LoadTexture("square.png");
	mQuad = new JQuad(mTexture, 1, 1, 32, 32);
	mQuad->SetHotSpot(16,16);

	
	b2BoxDef groundBoxDef;							// Define the ground box shape.
	
	groundBoxDef.extents.Set(300.0f, 10.0f);		// The extents are the half-widths of the box.
	groundBoxDef.density = 0.0f;					// Set the density of the ground box to zero. This will
													// make the ground body static (fixed).
	//groundBoxDef.friction = 0.1f;

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	groundBodyDef.AddShape(&groundBoxDef);			// Part of a body's def is its list of shapes.

	mWorld->CreateBody(&groundBodyDef);				// Call the body factory which allocates memory for the ground body
													// from a pool and creates the ground box shape (also from a pool).
													// The body is also added to the world.


	mBodies = new b2Body*[BOX_COUNT];

	// Define the dynamic body. We set its position,
	// add the box shape, and call the body factory.

	for (int i=0;i<BOX_COUNT;i++)
	{
		b2BoxDef boxDef;
		boxDef.extents.Set(BOX_SIZE, BOX_SIZE);
		boxDef.density = 1.0f;						// Set the box density to be non-zero, so it will be dynamic.
		boxDef.friction = 0.3f;						// Override the default friction.

		b2BodyDef bodyDef;
		bodyDef.position.Set(b2Random(-40.0f, 40.0f), b2Random(30.0f, 70.0f));
		bodyDef.linearVelocity = -0.5f * bodyDef.position;
		//bodyDef.angularVelocity = b2Random(-20.0f, 20.0f);
		bodyDef.AddShape(&boxDef);

		mBodies[i] = mWorld->CreateBody(&bodyDef);
		
	}

}


void FlyingBox::Render()
{
	JRenderer* renderer = JRenderer::GetInstance();

	for (int i=0;i<BOX_COUNT;i++)
	{
		b2Vec2 position = mBodies[i]->GetOriginPosition();
		float32 rotation = mBodies[i]->GetRotation();

		renderer->RenderQuad(mQuad, 240+position.x*mScale, 260-position.y*mScale, M_PI*2-rotation, 0.5f, 0.5f);
	}

}
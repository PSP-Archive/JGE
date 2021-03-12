#include <JGE.h>
#include <JRenderer.h>
#include <JTypes.h>

#include "FrictionTest.h"


FrictionTest::FrictionTest():
	JBox2D(BOX_SCALING)
{
	mTexture = NULL;
	mQuad = NULL;
	mBodies = NULL;
}



FrictionTest::~FrictionTest()
{
	SAFE_DELETE(mTexture);
	SAFE_DELETE(mQuad);
	SAFE_DELETE_ARRAY(mBodies);

}


void FrictionTest::Create()
{
	mTexture = JRenderer::GetInstance()->LoadTexture("square.png");
	mQuad = new JQuad(mTexture, 1, 1, 32, 32);
	mQuad->SetHotSpot(16,16);

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(50.0f, 10.0f);

		b2BodyDef bd;
		bd.position.Set(0.0f, -10.0f);
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}
	
	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(6.5f, 0.125f);

		b2BodyDef bd;
		bd.position.Set(-2.0f, 11.0f);
		bd.rotation = -0.25f;
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(0.125f, 0.5f);

		b2BodyDef bd;
		bd.position.Set(6.25f, 9.5f);
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(6.5f, 0.125f);

		b2BodyDef bd;
		bd.position.Set(2.0f, 7.0f);
		bd.rotation = 0.25f;
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(0.125f, 0.5f);

		b2BodyDef bd;
		bd.position.Set(-6.25f, 5.5f);
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(6.5f, 0.125f);

		b2BodyDef bd;
		bd.position.Set(-2.0f, 3.0f);
		bd.rotation = -0.25f;
		bd.AddShape(&sd);
		mWorld->CreateBody(&bd);
	}

	mBodies = new b2Body*[BOX_COUNT];

	{
		b2BoxDef sd;
		sd.type = e_boxShape;
		sd.extents.Set(0.5f, 0.5f);
		sd.density = 25.0f;

		b2BodyDef bd;
		bd.AddShape(&sd);

		float* friction = new float[BOX_COUNT];
		friction[0] = 0.75f;
		friction[1] = 0.50f;
		friction[2] = 0.25f;
		friction[3] = 0.10f;
		friction[4] = 0.00f;

		for (int i = 0; i < BOX_COUNT; ++i)
		{
			sd.friction = friction[i];
			bd.position.Set(-7.5f + 2.0f * i, 14.0f);
			mBodies[i] = mWorld->CreateBody(&bd);
		}

		delete [] friction;
	}

}


void FrictionTest::Render()
{
	JBox2D::Render();
	JRenderer* renderer = JRenderer::GetInstance();

 	for (int i=0;i<BOX_COUNT;i++)
 	{
 		b2Vec2 position = mBodies[i]->GetOriginPosition();
 		float32 rotation = mBodies[i]->GetRotation();
 
 		renderer->RenderQuad(mQuad, 240+position.x*mScale, 260-position.y*mScale, M_PI*2-rotation, 0.55f, 0.55f);
 	}


}
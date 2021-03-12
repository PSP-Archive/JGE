#include <JGE.h>
#include <JRenderer.h>
#include <JTypes.h>

#include "Ragdoll.h"


Ragdoll::Ragdoll():
	JBox2D(BOX_SCALING)
{
	mTexture = NULL;
	mQuad = NULL;
	mBodies = NULL;
}



Ragdoll::~Ragdoll()
{
	SAFE_DELETE(mTexture);
	SAFE_DELETE(mQuad);
	SAFE_DELETE_ARRAY(mBodies);

}

/*

b2RevoluteJoint* Box2DSystem::createRevoluteJoint(Ogre::Real x, Ogre::Real y, b2Body* b1, b2Body* b2)
{
	b2World* world = getWorld();
	b2RevoluteJointDef jd;
	jd.anchorPoint.Set(x,y);
	jd.body1 = b1;
	jd.body2 = b2;
	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&jd);

	Box2dFullJointDef jd2;
	jd2.type = e_revoluteJoint;
	jd2.revolute = jd;
	jd2.joint = joint;
	mJoints.push_back(jd2);
	return joint;
}

void Box2DSystem::createRagdoll(Ogre::Real x, Ogre::Real y, Ogre::Real size, 
								Ogre::Real density, Ogre::Real friction, Ogre::Real rest)
{
	startOperation(BOX_2D_RAGDOLL_OPERATION);

	b2World* world = getWorld();

	Ogre::Real head_size = size;
	Ogre::Real body_height = size * 2.5f;
	Ogre::Real body_width = size;
	Ogre::Real arm_height = size * 0.25f;
	Ogre::Real arm_length = size;
	Ogre::Real forearm_height = size * 0.25f;
	Ogre::Real forearm_length = size;
	Ogre::Real leg_width = size * 0.4f;
	Ogre::Real leg_height = size * 2.0f;
	Ogre::Real feet_width = size*1.25f;
	Ogre::Real feet_height = size*0.5f;

	Ogre::Real placement_scale = 1.05f;
	b2Body* head = createRigidCircle(head_size, x, y+body_height+head_size*placement_scale, density, friction, rest);
	b2Body* body = createRigidBox(body_width, body_height, x, y, 0.0f, density*2.0f, friction, rest);

	b2Body* arm1 = createRigidBox(arm_length, arm_height, x-(body_width+arm_length), y+body_height, 0.0f, density*2.0f, friction, rest);
	b2Body* arm2 = createRigidBox(arm_length, arm_height, x+body_width+arm_length, y+body_height, 0.0f, density*2.0f, friction, rest);

	b2Body* forearm1 = createRigidBox(forearm_length, forearm_height, x-(body_width+arm_length*2.0f + forearm_length*placement_scale), y+body_height, 0.0f, density*0.5f, friction, rest);
	b2Body* forearm2 = createRigidBox(forearm_length, forearm_height, x+body_width+arm_length*2.0f + forearm_length*placement_scale, y+body_height, 0.0f, density*0.5f, friction, rest);

	b2Body* leg1 = createRigidBox(leg_width, leg_height, x-(body_width+leg_width), y-(body_height+leg_height*0.75f), 0.0f, density*2.0f, friction, rest);
	b2Body* leg2 = createRigidBox(leg_width, leg_height, x+(body_width+leg_width), y-(body_height+leg_height*0.75f), 0.0f, density*2.0f, friction, rest);
	b2Body* feet1 = createRigidBox(feet_width, feet_height, x-(body_width+leg_width+feet_width*0.5f), y-(body_height+leg_height*2.0f), 0.0f, density*2.0f, friction, rest);
	b2Body* feet2 = createRigidBox(feet_width, feet_height, x+(body_width+leg_width+feet_width*0.5f), y-(body_height+leg_height*2.0f), 0.0f, density*2.0f, friction, rest);

	b2RevoluteJoint* joint;
	joint = createRevoluteJoint(x, y+body_height, head, body);

	joint = createRevoluteJoint(x-(body_width+arm_length*0.1f), y+body_height, arm1, body);
	joint = createRevoluteJoint(x+body_width+arm_length*0.1f, y+body_height, arm2, body);

	joint = createRevoluteJoint(x-(body_width+arm_length*2.0f+forearm_length*0.3f), y+body_height, forearm1, arm1);
	joint = createRevoluteJoint(x+body_width+arm_length*2.0f+forearm_length*0.3f, y+body_height, forearm2, arm2);

	joint = createRevoluteJoint(x-(body_width+leg_width), y-body_height, leg1, body);
	joint = createRevoluteJoint(x+body_width+leg_width, y-body_height, leg2, body);
	joint = createRevoluteJoint(x-(body_width+leg_width), y-(body_height+leg_height*2.0f), feet1, leg1);
	joint = createRevoluteJoint(x+(body_width+leg_width), y-(body_height+leg_height*2.0f), feet2, leg2);

	endOperation(BOX_2D_RAGDOLL_OPERATION);
}
*/


void Ragdoll::Create()
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


void Ragdoll::Render()
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

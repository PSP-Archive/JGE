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

#ifndef SLIDER_CRANK_H
#define SLIDER_CRANK_H

// A motor driven slider crank with joint friction.

class SliderCrank : public Test
{
public:
	SliderCrank()
	{
		b2Body* ground = NULL;
		{
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			bd.AddShape(&sd);
			ground = m_world->CreateBody(&bd);
		}

		{
			// Define crank.
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(0.5f, 2.0f);
			sd.density = 1.0f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			b2RevoluteJointDef rjd;

			b2Body* prevBody = ground;

			bd.position.Set(0.0f, 7.0f);
			b2Body* body = m_world->CreateBody(&bd);

			rjd.anchorPoint.Set(0.0f, 5.0f);
			rjd.body1 = prevBody;
			rjd.body2 = body;
			rjd.motorSpeed = 1.0f * b2_pi;
			rjd.motorTorque = 10000.0f;
			rjd.enableMotor = true;
			m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

			prevBody = body;

			// Define follower.
			sd.extents.Set(0.5f, 4.0f);
			bd.position.Set(0.0f, 13.0f);
			body = m_world->CreateBody(&bd);

			rjd.anchorPoint.Set(0.0f, 9.0f);
			rjd.body1 = prevBody;
			rjd.body2 = body;
			rjd.enableMotor = false;
			m_world->CreateJoint(&rjd);

			prevBody = body;

			// Define piston
			sd.extents.Set(1.5f, 1.5f);
			bd.position.Set(0.0f, 17.0f);
			body = m_world->CreateBody(&bd);

			rjd.anchorPoint.Set(0.0f, 17.0f);
			rjd.body1 = prevBody;
			rjd.body2 = body;
			m_world->CreateJoint(&rjd);

			b2PrismaticJointDef pjd;
			pjd.anchorPoint.Set(0.0f, 17.0f);
			pjd.body1 = ground;
			pjd.body2 = body;
			pjd.axis.Set(0.0f, 1.0f);
			pjd.motorSpeed = 0.0f;		// joint friction
			pjd.motorForce = 1000.0f;
			pjd.enableMotor = true;

			m_joint2 = (b2PrismaticJoint*)m_world->CreateJoint(&pjd);

			// Create a payload
			sd.density = 2.0f;
			bd.position.Set(0.0f, 23.0f);
			m_world->CreateBody(&bd);
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'f':
			m_joint2->m_enableMotor = !m_joint2->m_enableMotor;
			m_joint2->GetBody2()->WakeUp();
			break;

		case 'm':
			m_joint1->m_enableMotor = !m_joint1->m_enableMotor;
			m_joint1->GetBody2()->WakeUp();
			break;
		}
	}

	void Step(const Settings* settings)
	{
		DrawString(5, m_textLine, "Keys: (f) toggle friction, (m) toggle motor");
		m_textLine += 15;
		float32 torque = m_joint1->GetMotorTorque(settings->hz);
		DrawString(5, m_textLine, "Motor Torque = %5.0f", torque);
		m_textLine += 15;
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new SliderCrank;
	}

	b2RevoluteJoint* m_joint1;
	b2PrismaticJoint* m_joint2;
};

#endif

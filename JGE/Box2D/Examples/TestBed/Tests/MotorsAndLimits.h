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

#ifndef MOTORS_AND_LIMITS_H
#define MOTORS_AND_LIMITS_H

class MotorsAndLimits : public Test
{
public:
	MotorsAndLimits()
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
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(2.0f, 0.5f);
			sd.density = 5.0f;
			sd.friction = 0.05f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			b2RevoluteJointDef rjd;
			
			b2Body* body = NULL;
			b2Body* prevBody = ground;
			const float32 y = 8.0f;

			bd.position.Set(3.0f, y);
			body = m_world->CreateBody(&bd);

			rjd.anchorPoint.Set(0.0f, y);
			rjd.body1 = prevBody;
			rjd.body2 = body;
			rjd.motorSpeed = 1.0f * b2_pi;
			rjd.motorTorque = 10000.0f;
			rjd.enableMotor = true;
			
			m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

			prevBody = body;

			bd.position.Set(9.0f, y);
			body = m_world->CreateBody(&bd);

			rjd.anchorPoint.Set(6.0f, y);
			rjd.body1 = prevBody;
			rjd.body2 = body;
			rjd.motorSpeed = 0.5f * b2_pi;
			rjd.motorTorque = 2000.0f;
			rjd.enableMotor = true;
			rjd.lowerAngle = - 0.5f * b2_pi;
			rjd.upperAngle = 0.5f * b2_pi;
			//rjd.enableMotor = false;
			//rjd.minAngle = 0.0f;
			//rjd.maxAngle = 0.0f;
			rjd.enableLimit = true;

			m_joint2 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

			bd.position.Set(-10.0f, 10.0f);
			bd.rotation = 0.5f * b2_pi;
			body = m_world->CreateBody(&bd);

			b2PrismaticJointDef pjd;
			pjd.anchorPoint.Set(-10.0f, 10.0f);
			pjd.body1 = ground;
			pjd.body2 = body;
			pjd.axis.Set(1.0f, 0.0f);
			pjd.motorSpeed = 10.0f;
			pjd.motorForce = 1000.0f;
			pjd.enableMotor = true;
			pjd.lowerTranslation = 0.0f;
			pjd.upperTranslation = 20.0f;
			pjd.enableLimit = true;

			m_joint3 = (b2PrismaticJoint*)m_world->CreateJoint(&pjd);
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'l':
			m_joint2->m_enableLimit = !m_joint2->m_enableLimit;
			m_joint3->m_enableLimit = !m_joint3->m_enableLimit;
			m_joint2->m_body1->WakeUp();
			m_joint2->m_body2->WakeUp();
			m_joint3->m_body2->WakeUp();
			break;

		case 'm':
			m_joint1->m_enableMotor = !m_joint1->m_enableMotor;
			m_joint2->m_enableMotor = !m_joint2->m_enableMotor;
			m_joint3->m_enableMotor = !m_joint3->m_enableMotor;
			m_joint2->m_body1->WakeUp();
			m_joint2->m_body2->WakeUp();
			m_joint3->m_body2->WakeUp();
			break;

		case 'p':
			m_joint3->m_body2->WakeUp();
			m_joint3->m_motorSpeed = -m_joint3->m_motorSpeed;
			break;
		}
	}

	void Step(const Settings* settings)
	{
		DrawString(5, m_textLine, "Keys: (l) limits, (m) motors, (p) prismatic speed");
		m_textLine += 15;
		float32 torque1 = m_joint1->GetMotorTorque(settings->hz);
		float32 torque2 = m_joint2->GetMotorTorque(settings->hz);
		float32 force3 = m_joint3->GetMotorForce(settings->hz);
		DrawString(5, m_textLine, "Motor Torque = %4.0f, %4.0f : Motor Force = %4.0f", torque1, torque2, force3);
		m_textLine += 15;
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new MotorsAndLimits;
	}

	b2RevoluteJoint* m_joint1;
	b2RevoluteJoint* m_joint2;
	b2PrismaticJoint* m_joint3;
};

#endif

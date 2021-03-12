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

#ifndef CCD_TEST_H
#define CCD_TEST_H

class CCDTest : public Test
{
public:

	CCDTest()
	{
		m_world->m_gravity.SetZero();
#if 1
		{
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(0.1f, 10.0f);
			sd.density = 0.0f;

			b2BodyDef bd;
			bd.position.Set(0.0f, 20.0f);
			//bd.linearVelocity.Set(400.0f, 0.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}
#else
		{
			b2CircleDef sd;
			sd.type = e_circleShape;
			sd.radius = 1.0f;
			sd.density = 1.0f;

			b2BodyDef bd;
			bd.position.Set(-50.0f, 20.0f);
			bd.linearVelocity.Set(400.0f, 0.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}
#endif

#if 1
		{
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(0.1f, 2.0f);
			sd.density = 1.0f;
			sd.restitution = 0.0f;

			m_angularVelocity = -35.268715f; //b2Random(-50.0f, 50.0f);

			b2BodyDef bd;
			bd.position.Set(50.0f, 20.0f);
			bd.linearVelocity.Set(-200.0f, 0.0f);
			bd.angularVelocity = m_angularVelocity;
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}
#else
		{
			b2CircleDef sd;
			sd.type = e_circleShape;
			sd.radius = 0.5f;
			sd.density = 1.0f;
			sd.restitution = 0.02f;

			b2BodyDef bd;
			bd.position.Set(50.0f, 20.0f);
			bd.linearVelocity.Set(-400.0f, 0.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}
#endif
	}

	static Test* Create()
	{
		return new CCDTest;
	}

	float32 m_angularVelocity;
};

#endif

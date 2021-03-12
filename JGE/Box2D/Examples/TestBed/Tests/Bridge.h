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

#ifndef BRIDGE_H
#define BRIDGE_H

class Bridge : public Test
{
public:
	Bridge()
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
			sd.extents.Set(0.5f, 0.125f);
			sd.density = 20.0f;
			sd.friction = 0.2f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			b2RevoluteJointDef jd;
			const int32 numPlanks = 30;

			b2Body* prevBody = ground;
			for (int i = 0; i < numPlanks; ++i)
			{
				bd.position.Set(-14.5f + 1.0f * i, 5.0f);
				b2Body* body = m_world->CreateBody(&bd);

				jd.anchorPoint.Set(-15.0f + 1.0f * i, 5.0f);
				jd.body1 = prevBody;
				jd.body2 = body;
				m_world->CreateJoint(&jd);

				prevBody = body;
			}

			jd.anchorPoint.Set(-15.0f + 1.0f * numPlanks, 5.0f);
			jd.body1 = prevBody;
			jd.body2 = ground;
			m_world->CreateJoint(&jd);
		}
	}

	static Test* Create()
	{
		return new Bridge;
	}
};

#endif

/*
* Copyright (c) 2007 Erin Catto http://www.gphysics.com
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

#ifndef CRADLE_H
#define CRADLE_H

// Note this is a very tricky problem to get right.
// See: http://www.bulletphysics.com/Bullet/phpBB3/viewtopic.php?f=4&t=1584
// I'm using a gap, but the simulation still breaks down after a few swings.
class Cradle : public Test
{
public:
	Cradle()
	{
		b2BroadPhase::s_validate = true;

		b2Body* ground = m_world->GetGroundBody();

		{
			b2CircleDef sd;
			sd.radius = 0.25f;
			sd.density = 20.0f;
			sd.friction = 0.0f;
			sd.restitution = 1.0f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			b2RevoluteJointDef jd;

			const float32 y = 5.0f;
			const float32 L = 2.0f;

			for (int32 i = 0; i < 5; ++i)
			{
				float32 x = sd.radius * (2.02f * i - 5.0f);
				bd.position.Set(x, y);
				//float32 w = 100.0f;
				//bd.angularVelocity = w;
				//bd.linearVelocity.Set(w * L, 0.0f);
				b2Body* body = m_world->CreateBody(&bd);

				jd.anchorPoint.Set(x, y + L);
				jd.body1 = ground;
				jd.body2 = body;
				m_world->CreateJoint(&jd);
			}
		}
	}

	~Cradle()
	{
		b2BroadPhase::s_validate = false;
	}

	static Test* Create()
	{
		return new Cradle;
	}
};

#endif

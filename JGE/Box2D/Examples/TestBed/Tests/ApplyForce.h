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

#ifndef APPLY_FORCE_H
#define APPLY_FORCE_H

class ApplyForce : public Test
{
public:
	ApplyForce()
	{
		m_world->m_gravity.Set(0.0f, 0.0f);

		{
			b2BoxDef sd;
			sd.extents.Set(50.0f, 10.0f);
			sd.restitution = 0.9f;

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);

			bd.position.Set(30.0f, 50.0f);
			bd.rotation = 0.5f * b2_pi;
			m_world->CreateBody(&bd);

			bd.position.Set(-30.0f, 50.0f);
			bd.rotation = -0.5f * b2_pi;
			m_world->CreateBody(&bd);

			bd.position.Set(0.0f, 40.0f);
			bd.rotation = 0.0f;
			m_world->CreateBody(&bd);
		}

		{
			b2PolyDef sd1;
			sd1.vertexCount = 3;
			sd1.vertices[0].Set(-1.0f, 0.0f);
			sd1.vertices[1].Set(1.0f, 0.0f);
			sd1.vertices[2].Set(0.0f, 0.5f);
			sd1.localRotation = 0.3524f * b2_pi;
			b2Mat22 R1(sd1.localRotation);
			sd1.localPosition = b2Mul(R1, b2Vec2(1.0f, 0.0f));
			sd1.density = 2.0f;
			sd1.restitution = 0.9f;

			b2PolyDef sd2;
			sd2.vertexCount = 3;
			sd2.vertices[0].Set(-1.0f, 0.0f);
			sd2.vertices[1].Set(1.0f, 0.0f);
			sd2.vertices[2].Set(0.0f, 0.5f);
			sd2.localRotation = -0.3524f * b2_pi;
			b2Mat22 R2(sd2.localRotation);
			sd2.localPosition = b2Mul(R2, b2Vec2(-1.0f, 0.0f));
			sd2.density = 2.0f;
			sd2.restitution = 0.9f;

			b2BodyDef bd;
			bd.AddShape(&sd1);
			bd.AddShape(&sd2);
			bd.allowSleep = false;
			bd.angularDamping = 0.02f;
			bd.linearDamping = 0.02f;

			bd.position.Set(0.0f, 1.05f);
			bd.rotation = b2_pi;
			m_body = m_world->CreateBody(&bd);
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'w':
			{
				b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -200.0f));
				b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.0f));
				m_body->ApplyForce(f, p);
			}
			break;

		case 'a':
			{
				m_body->ApplyTorque(20.0f);
			}
			break;

		case 'd':
			{
				m_body->ApplyTorque(-20.0f);
			}
			break;
		}
	}

	static Test* Create()
	{
		return new ApplyForce;
	}

	b2Body* m_body;
};

#endif

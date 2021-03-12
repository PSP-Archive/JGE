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

#ifndef VARYING_FRICTION_H
#define VARYING_FRICTION_H

class VaryingFriction : public Test
{
public:

	VaryingFriction()
	{
		float32 scale = 2.0f;

		{
			b2BoxDef sd;
			sd.extents.Set(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(6.5f, 0.125f);
			sd.extents *= scale;

			b2BodyDef bd;
			bd.position.Set(-2.0f, 11.0f);
			bd.position *= scale;

			bd.rotation = -0.25f;
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(0.125f, 0.5f);
			sd.extents *= scale;

			b2BodyDef bd;
			bd.position.Set(5.25f, 9.5f);
			bd.position *= scale;

			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(6.5f, 0.125f);
			sd.extents *= scale;

			b2BodyDef bd;
			bd.position.Set(2.0f, 7.0f);
			bd.position *= scale;

			bd.rotation = 0.25f;
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(0.125f, 0.5f);
			sd.extents *= scale;

			b2BodyDef bd;
			bd.position.Set(-5.25f, 5.5f);
			bd.position *= scale;

			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(6.5f, 0.125f);
			sd.extents *= scale;

			b2BodyDef bd;
			bd.position.Set(-2.0f, 3.0f);
			bd.position *= scale;

			bd.rotation = -0.25f;
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			sd.extents.Set(0.25f, 0.25f);
			sd.extents *= scale;

			sd.density = 25.0f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			float friction[5] = {0.75f, 0.5f, 0.35f, 0.1f, 0.0f};

			for (int i = 0; i < 5; ++i)
			{
				sd.friction = friction[i];
				bd.position.Set(-7.5f + 2.0f * i, 14.0f);
				bd.position *= scale;
				m_world->CreateBody(&bd);
			}
		}
	}

	static Test* Create()
	{
		return new VaryingFriction;
	}
};

#endif

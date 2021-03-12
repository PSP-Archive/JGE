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

#ifndef VERTICAL_STACK_H
#define VERTICAL_STACK_H

class VerticalStack : public Test
{
public:
	VerticalStack()
	{
		{
			b2BoxDef sd;
			sd.type = e_boxShape;
			sd.extents.Set(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			bd.AddShape(&sd);
			m_world->CreateBody(&bd);
		}

		{
			b2BoxDef sd;
			float32 a = 0.5f;
			sd.type = e_boxShape;
			sd.extents.Set(a, a);
			sd.density = 1.0f;
			sd.friction = 0.3f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			for (int i = 0; i < 14; ++i)
			{
				//float32 x = b2Random(-0.1f, 0.1f);
				//float32 x = i % 2 == 0 ? -0.025f : 0.025f;
				//bd.position.Set(x, 0.752f + 1.54f * i);
				bd.position.Set(0.0f, 0.51f + 1.02f * i);
				m_world->CreateBody(&bd);
			}
		}
	}

	static Test* Create()
	{
		return new VerticalStack;
	}
};

#endif

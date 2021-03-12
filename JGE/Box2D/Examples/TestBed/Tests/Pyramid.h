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

#ifndef PYRAMID_H
#define PYRAMID_H

class Pyramid : public Test
{
public:
	Pyramid()
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
			sd.density = 5.0f;

			b2BodyDef bd;
			bd.AddShape(&sd);

			b2Vec2 x = b2Vec2::Make(-10.0f, 0.75f);
			b2Vec2 y;
			b2Vec2 deltaX = b2Vec2::Make(0.5625f, 2.0f);
			b2Vec2 deltaY = b2Vec2::Make(1.125f, 0.0f);

			for (int32 i = 0; i < 25; ++i)
			{
				y = x;

				for (int32 j = i; j < 25; ++j)
				{
					bd.position = y;
					m_world->CreateBody(&bd);

					y += deltaY;
				}

				x += deltaX;
			}
		}
	}

	static Test* Create()
	{
		return new Pyramid;
	}
};

#endif

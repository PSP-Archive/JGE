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

#ifndef COMPOUND_SHAPES_H
#define COMPOUND_SHAPES_H

class CompoundShapes : public Test
{
public:
	CompoundShapes()
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
			b2CircleDef sd1;
			sd1.radius = 0.5f;
			sd1.localPosition.Set(-0.5f, 0.5f);
			sd1.density = 2.0f;

			b2CircleDef sd2;
			sd2.radius = 0.5f;
			sd2.localPosition.Set(0.5f, 0.5f);
			sd2.density = 0.0f; // massless

			b2BodyDef bd;
			bd.AddShape(&sd1);
			bd.AddShape(&sd2);

			for (int i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				bd.position.Set(x + 5.0f, 1.05f + 2.5f * i);
				bd.rotation = b2Random(-b2_pi, b2_pi);
				m_world->CreateBody(&bd);
			}
		}

		{
			b2BoxDef sd1;
			sd1.extents.Set(0.25f, 0.5f);
			sd1.density = 2.0f;

			b2BoxDef sd2;
			sd2.extents.Set(0.25f, 0.5f);
			sd2.localPosition.Set(0.0f, -0.5f);
			sd2.localRotation = 0.5f * b2_pi;
			sd2.density = 2.0f;

			b2BodyDef bd;
			bd.AddShape(&sd1);
			bd.AddShape(&sd2);

			for (int i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				bd.position.Set(x - 5.0f, 1.05f + 2.5f * i);
				bd.rotation = b2Random(-b2_pi, b2_pi);
				m_world->CreateBody(&bd);
			}
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

			b2PolyDef sd2;
			sd2.vertexCount = 3;
			sd2.vertices[0].Set(-1.0f, 0.0f);
			sd2.vertices[1].Set(1.0f, 0.0f);
			sd2.vertices[2].Set(0.0f, 0.5f);
			sd2.localRotation = -0.3524f * b2_pi;
			b2Mat22 R2(sd2.localRotation);
			sd2.localPosition = b2Mul(R2, b2Vec2(-1.0f, 0.0f));
			sd2.density = 2.0f;

			b2BodyDef bd;
			bd.AddShape(&sd1);
			bd.AddShape(&sd2);

			for (int32 i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				bd.position.Set(x, 2.05f + 2.5f * i);
				bd.rotation = 0.0f;
				m_world->CreateBody(&bd);
			}
		}

		{
			b2BoxDef sd_bottom;
			sd_bottom.extents.Set( 1.5f, 0.15f );
			sd_bottom.density = 4.0f;

			b2BoxDef sd_left;
			sd_left.extents.Set( 0.15f, 2.7f );
			sd_left.localPosition.Set( -1.45f, 2.35f );
			sd_left.localRotation = 0.2f;
			sd_left.density = 4.0f;

			b2BoxDef sd_right;
			sd_right.extents.Set( 0.15f, 2.7f );
			sd_right.localPosition.Set( 1.45f, 2.35f );
			sd_right.localRotation = -0.2f;
			sd_right.density = 4.0f;

			b2BodyDef bd;
			bd.position.Set( 0.0f, 2.0f );
			bd.AddShape( &sd_bottom );
			bd.AddShape( &sd_left );
			bd.AddShape( &sd_right );

			m_world->CreateBody(&bd);
		}
	}

	static Test* Create()
	{
		return new CompoundShapes;
	}
};

#endif

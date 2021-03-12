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

#include "Render.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/gl/glut.h"
#endif

#include <cstdio>
#include <cstdarg>

void DrawJoint(b2Joint* joint)
{
	b2Body* b1 = joint->m_body1;
	b2Body* b2 = joint->m_body2;
	b2Vec2 x1 = b1->m_position;
	b2Vec2 x2 = b2->m_position;
	b2Vec2 p1 = joint->GetAnchor1();
	b2Vec2 p2 = joint->GetAnchor2();

	glColor3f(0.5f, 0.8f, 0.8f);
	glBegin(GL_LINES);

	switch (joint->m_type)
	{
	case e_distanceJoint:
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		break;

	case e_pulleyJoint:
		{
			b2PulleyJoint* pulley = (b2PulleyJoint*)joint;
			b2Vec2 s1 = pulley->GetGroundPoint1();
			b2Vec2 s2 = pulley->GetGroundPoint2();
			glVertex2f(s1.x, s1.y);
			glVertex2f(p1.x, p1.y);
			glVertex2f(s2.x, s2.y);
			glVertex2f(p2.x, p2.y);
		}
		break;

	default:
		glVertex2f(x1.x, x1.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(x2.x, x2.y);
		glVertex2f(p2.x, p2.y);
	}

	glEnd();
}

void DrawShape(const b2Shape* shape, const Color& c)
{
	switch (shape->m_type)
	{
	case e_circleShape:
		{
			const b2CircleShape* circle = (const b2CircleShape*)shape;
			b2Vec2 x = circle->m_position;
			float32 r = circle->m_radius;
			const float32 k_segments = 16.0f;
			const float32 k_increment = 2.0f * b2_pi / k_segments;
			glColor4f(c.cx, c.cy, c.cz, 1.0f);
			glBegin(GL_LINE_LOOP);
			float32 theta = 0.0f;
			for (int32 i = 0; i < k_segments; ++i)
			{
				b2Vec2 d(r * cosf(theta), r * sinf(theta));
				b2Vec2 v = x + d;
				glVertex2f(v.x, v.y);
				theta += k_increment;
			}
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(x.x, x.y);
			b2Vec2 ax = circle->m_R.col1;
			glVertex2f(x.x + r * ax.x, x.y + r * ax.y);
			glEnd();
		}
		break;

	case e_polyShape:
		{
			const b2PolyShape* poly = (const b2PolyShape*)shape;
			glColor4f(c.cx, c.cy, c.cz, 1.0f);
			glBegin(GL_LINE_LOOP);
			for (int32 i = 0; i < poly->m_vertexCount; ++i)
			{
				b2Vec2 v = poly->m_position + b2Mul(poly->m_R, poly->m_vertices[i]);
				glVertex2f(v.x, v.y);
			}
			glEnd();

		}
		break;
	}
}

void DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void DrawAABB(b2AABB* aabb, const Color& c)
{
	glColor4f(c.cx, c.cy, c.cz, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(aabb->minVertex.x, aabb->minVertex.y);
	glVertex2f(aabb->maxVertex.x, aabb->minVertex.y);
	glVertex2f(aabb->maxVertex.x, aabb->maxVertex.y);
	glVertex2f(aabb->minVertex.x, aabb->maxVertex.y);
	glEnd();
}

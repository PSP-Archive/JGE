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

#ifndef RENDER_H
#define RENDER_H

#include "Box2D.h"

class b2Joint;
class b2Shape;
struct b2AABB;

struct Color
{
	Color() { cx = 1.0f; cy = 1.0f; cz = 1.0f; }
	Color(float32 x, float32 y, float32 z) { cx = x; cy = y; cz = z; }
	float32 cx, cy, cz;
};

void DrawJoint(b2Joint* joint);
void DrawShape(const b2Shape* shape, const Color& color);
void DrawString(int x, int y, const char* string, ...);
void DrawAABB(b2AABB* aabb, const Color& c);

#endif

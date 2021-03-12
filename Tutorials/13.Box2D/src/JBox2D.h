#ifndef _JBOX2D_H_
#define _JBOX2D_H_

#include "Box2D.h"

class JBox2D
{

public:

	JBox2D(float scale = 1.0f);
	virtual ~JBox2D();

	virtual void Update(float dt);
	virtual void Render();

	virtual void Create() = 0;

private:
	float mTimer;

protected:
	b2World* mWorld;
	float mScale;
};

#endif


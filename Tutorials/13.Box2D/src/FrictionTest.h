#ifndef _FRICTIONTEST_H_
#define _FRICTIONTEST_H_

#include "JBox2D.h"

#define BOX_COUNT		5
#define BOX_SCALING		16.0f

class FrictionTest: public JBox2D
{
public:
	FrictionTest();
	~FrictionTest();

	virtual void Render();
	virtual void Create();

private:
	b2Body** mBodies;

	JTexture* mTexture;
	JQuad* mQuad;
};

#endif


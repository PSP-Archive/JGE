#ifndef _FLYINGBOX_H_
#define _FLYINGBOX_H_

#include "JBox2D.h"

#define BOX_COUNT		100
#define BOX_SIZE		2.0f
#define BOX_SCALING		4.0f

class FlyingBox: public JBox2D
{
public:
	FlyingBox();
	~FlyingBox();

	virtual void Render();
	virtual void Create();

private:
	b2Body** mBodies;

	JTexture* mTexture;
	JQuad* mQuad;
};

#endif


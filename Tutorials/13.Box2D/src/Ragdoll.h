#ifndef _RAGDOLL_H_
#define _RAGDOLL_H_

#include "JBox2D.h"

#define BOX_COUNT		5
#define BOX_SCALING		16.0f

class Ragdoll: public JBox2D
{
public:
	Ragdoll();
	~Ragdoll();

	virtual void Render();
	virtual void Create();

private:
	b2Body** mBodies;

	JTexture* mTexture;
	JQuad* mQuad;
};

#endif


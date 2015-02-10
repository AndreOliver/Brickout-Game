#pragma once
#include "TGame.h"
#include "TSprite.h"

class BulletSprite :
	public TSprite
{
public:

	BulletSprite(string textureFileName="ball02.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		setScale(0.125f);
		edgeBehaviour=INACTIVATE;
		isActive=false;
	}

	virtual ~BulletSprite(void)
	{
	}

	virtual void hasCollidedWith(TSprite * pCollidedWith)
	{
		isActive=false;
	}



};


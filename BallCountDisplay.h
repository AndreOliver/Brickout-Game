#pragma once
#include "TSprite.h"
class BallCountDisplay :
	public TSprite
{
public:

	BallCountDisplay(string textureFileName=(string)"Ball02.png")
	{	
		setTexture(TGlobal::resources.getTexture(textureFileName));
		//setColor(TGlobal::randomBrightColor());
		setScale(0.25f);
		setRotation(0.0f);
		setRotationSpeed(100.0f);
		setRotationAcceleration(0.0f);
		setPosition((float)(TGlobal::pMainWindow->getSize().x-30),30.0f);
		isActive=true;
	}

	virtual ~BallCountDisplay(void)
	{
	}

	virtual void draw(sf::RenderWindow & displayWindow)
	{
		if(isActive)
		{
			for(int i=0;i<TGlobal::ballsLeft;i++)
			{
				baseSprite.setPosition(position.x-20*i,position.y);
				displayWindow.draw(baseSprite);
			}
		}
	}

};


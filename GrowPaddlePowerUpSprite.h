#pragma once
#include "powerupsprite.h"
class GrowPaddlePowerUpSprite :
	public PowerUpSprite
{
public:

	GrowPaddlePowerUpSprite(string textureFileName="Ball02.png")
	{
		setup(textureFileName);
		setColor(255,0,255,255);
		setScale(0.4f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(1);

	}
	
	virtual void applyPowerup()
	{
		TPlayers::pPaddle->changeState(PADDLESTATE_LARGE);
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}


	virtual ~GrowPaddlePowerUpSprite(void)
	{
	}
};


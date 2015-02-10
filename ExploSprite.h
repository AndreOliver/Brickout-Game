#pragma once
#include "TGame.h"
#include "TSprite.h"

class ExploSprite :
	public TSprite
{
public:

	ExploSprite(string textureFileName="explosion.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		friction=0.0f;
		edgeBehaviour=INACTIVATE;
		isActive=false;
		maxScale=1.0f;
	}

	virtual ~ExploSprite(void)
	{
	}


#define EXPLO_STATE_START 0
#define EXPLO_STATE_END 1



	virtual void update(sf::Time elapsed)
	{
		if(isActive)
		{
			timeInState+=elapsed.asSeconds();
			switch(state)
			{
			case EXPLO_STATE_START:
				if(firstTimeInState)
				{
					firstTimeInState=false;
					setScale(0.1f);
				}
				multiplyScaleBy(1.0f+elapsed.asSeconds()*20.0f);
				rotation=TGlobal::randomAngle();
				if(getScaleX()>maxScale)
				{
					changeState(EXPLO_STATE_END);
				}
				break;
			
			case EXPLO_STATE_END:
				if(firstTimeInState)
				{
					firstTimeInState=false;
				}
				multiplyScaleBy(1.0f-elapsed.asSeconds()*40.0f);
				rotation=TGlobal::randomAngle();
				if(getScaleX()<0.1f)
				{
					isActive=false;
				}
				break;
			}
		}
		TSprite::update(elapsed);
	}


	void setMaxScale(float ms)
	{
		maxScale=ms;
	}

private:

	float maxScale;

};


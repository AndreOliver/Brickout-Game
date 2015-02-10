#pragma once
#include "TGame.h"
#include "TSprite.h"

class ParticleSprite :
	public TSprite
{
public:

	ParticleSprite(string textureFileName="particle.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		edgeBehaviour=INACTIVATE;
		isActive=false;
		friction =4.0f;
		duration=0.3f;
		swarmDestiny1=sf::Vector2f(0.0f,0.0f);
	}

	virtual ~ParticleSprite(void)
	{
	}


#define PARTICLE_STATE_START 0
#define PARTICLE_STATE_END 1
#define PARTICLE_STATE_START_SWARM 2



	virtual void update(sf::Time elapsed)
	{
		if(isActive)
		{
			timeInState+=elapsed.asSeconds();
			switch(state)
			{
			case PARTICLE_STATE_START:
				if(firstTimeInState)
				{
					firstTimeInState=false;
					setOpacity(255);
					setScale(3.0f);
				}
				if(timeInState>duration)
				{
					changeState(PARTICLE_STATE_END);
				}
				break;
			
			case PARTICLE_STATE_END:
				if(firstTimeInState)
				{
					firstTimeInState=false;
				}
				setOpacity(getOpacity()-3);
				if(getOpacity()<=1)
				{
					isActive=false;
				}
				break;
			case PARTICLE_STATE_START_SWARM:
				if(firstTimeInState)
				{
					setScale(1.5f);
					//setSpeedByAngle(TGlobal::randomAngle(),TGlobal::randomF(50.0f,200.0f));
					setOpacity(196);
					firstTimeInState=false;
					friction=2.0f;
					swarmFactor=0.8f;
					swarmFactor2=1.0f;
				}
				swarmFactor+=2.0f*elapsed.asSeconds();
				speed.x+= swarmFactor*elapsed.asSeconds() * (((TSprite *)(TPlayers::pShip))->getPosition().x-position.x);
				speed.y+= swarmFactor*elapsed.asSeconds() * (((TSprite *)(TPlayers::pShip))->getPosition().y-position.y);

				swarmFactor2-=0.5f*elapsed.asSeconds();
				if(swarmFactor2<0.0f)swarmFactor2=0.0f;
				speed.x+= swarmFactor2*elapsed.asSeconds() * (swarmDestiny1.x-position.x);
				speed.y+= swarmFactor2*elapsed.asSeconds() * (swarmDestiny1.y-position.y);



				//if((TPlayers::distance(((TSprite *)(TPlayers::pShip)),this) < ((TSprite *)(TPlayers::pShip))->getScaledCollisionCircleRadius()) || (timeInState>duration))
				if((TPlayers::distance(((TSprite *)(TPlayers::pShip)),this) < 4.0f) || (timeInState>duration))
				{
					isActive=false;
				}
				break;
			}
		}
		TSprite::update(elapsed);
	}


	void setDuration(float d)
	{
		duration = d;
	}

	void setSwarmDestiny(sf::Vector2f v)
	{
		swarmDestiny1=v;
	}


protected:

	float duration;
	sf::Vector2f swarmDestiny1;
	float swarmFactor;
	float swarmFactor2;

};


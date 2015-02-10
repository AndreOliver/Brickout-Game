#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "BulletSprite.h"
#include "ExploSprite.h"
#include "ParticleSprite.h"
#include "TPlayers.h"


class CrystalSprite :
	public TSprite
{
public:

	CrystalSprite(string textureFileName="")
	{
		switch(rand()%4)
		{
		case 0:
			textureFileName="oneCrystal2Bright.png";
			break;
		case 1:
			textureFileName="CrystalB002Bright.png";
			break;
		case 2:
			textureFileName="CrystalC002Bright.png";
			break;
		case 3:
			textureFileName="CrystalD003Bright.png";
			break;
		}
		setTexture(TGlobal::resources.getTexture(textureFileName));
		setColor(TGlobal::randomBrightColor());
		setRotation(TGlobal::randomF(0.0f,360.0f));
		setRotationSpeed(TGlobal::randomF(-100.0f,100.0f));
		//setRotationAcceleration(TGlobal::randomF(-10.0f,10.0f));
		friction=0.0f;
		edgeBehaviour=PREACTIVATE;
		setNextEdgeBehaviour(BOUNCE);
		isActive=false;

	}

	virtual void hasCollidedWith(TSprite * pCollidedWith)
	{
		BulletSprite * pS = dynamic_cast<BulletSprite *>(pCollidedWith);
		if(pS)
		{
			isActive=false;
			//crystal has collided with bullet
			if(getScaleX()>0.15)
			{
				for(int i=0;i<3;i++)
				{
					CrystalSprite * pS = (CrystalSprite *) TPlayers::pCrystalList->getPointerToNextInactive();
					if(pS)
					{
						pS->isActive=true;
						pS->setPosition(position);
						pS->setColor(TGlobal::randomChangeColor(getColor(),40));
						pS->setScale(getScaleX()/2.0f);
						pS->setSpeedByAngle(TGlobal::randomAngle(),TGlobal::randomF(40.0f,80.0f));
						pS->addSpeed(getSpeed());
						pS->addSpeed(pCollidedWith->getSpeed()*0.1f);
						pS->setEdgeBehaviour(PREACTIVATE);
						pS->setNextEdgeBehaviour(BOUNCE);
					}
				}
				ExploSprite * pES  = (ExploSprite *) TPlayers::pExploList->getPointerToNextInactive();
				if(pES)
				{
					pES->setPosition(position);
					pES->isActive=true;
					pES->setMaxScale(getScaleX()*4.0f);
					pES->changeState(EXPLO_STATE_START);
				}
				//for(int i=0;i<20;i++)
				//{
				//	ParticleSprite * pS = (ParticleSprite *) TPlayers::pParticleList->getPointerToNextInactive();
				//	if(pS)
				//	{
				//		pS->isActive=true;
				//		pS->setDuration(0.3f);
				//		pS->setPosition(position);
				//		pS->setSpeedByAngle(TGlobal::randomAngle(),TGlobal::randomF(400.0f,800.0f));
				//		pS->addSpeed(pCollidedWith->getSpeed()*0.25f);
				//		pS->changeState(PARTICLE_STATE_START);
				//	}
				//}
			}
			else
			{
				sf::Vector2f offset=((TSprite *)TPlayers::pShip)->getPosition()+TGlobal::randVector2f(-400,400,-400,400);
				//float rAngle=TGlobal::randomAngle();
				for(int i=0;i<100;i++)
				{
					ParticleSprite * pS = (ParticleSprite *) TPlayers::pParticleList->getPointerToNextInactive();
					if(pS)
					{
						pS->isActive=true;
						pS->setDuration(30.0f);
						pS->setPosition(position);
						pS->setSwarmDestiny(offset);
						pS->setColor(TGlobal::randomChangeColor(getColor(),30));
						
						pS->setSpeedByAngle(TGlobal::randomAngle(),TGlobal::randomF(10.0f,400.0f));
						//pS->setSpeedByAngle(rAngle+TGlobal::randomF(-90.0f,90.0f),TGlobal::randomF(10.0f,1800.0f));
						//pS->addSpeed(pCollidedWith->getSpeed()*0.25f);
						pS->changeState(PARTICLE_STATE_START_SWARM);
					}
				}
			}
		}
	}





	virtual ~CrystalSprite(void)
	{
	}
};


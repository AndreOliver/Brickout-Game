#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "TPlayers.h"
#include "BulletSprite.h"

class ShipSprite :
	public TSprite
{
public:

	ShipSprite(string textureFileName=(string)"ship4.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		setScale(0.25f);
		friction=0.3f;
		edgeBehaviour=BOUNCE;
		setPosition(sf::Vector2f(TGlobal::pMainWindow->getSize().x/2.0f,TGlobal::pMainWindow->getSize().y/2.0f));
		hotGunTime=0.0f;
		startHotGunTime=0.1f;

	}

 	virtual void update(sf::Time elapsed)
	{
		float rotFactor=120.0f*elapsed.asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rotation-=rotFactor;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rotation+=rotFactor;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			float accelConstant=300.f*elapsed.asSeconds();
			speed.x=cosf((rotation/180.f)*3.1459f)*accelConstant+speed.x;
			speed.y=sinf((rotation/180.f)*3.1459f)*accelConstant+speed.y;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			float brake=1.0f-(2.0f*elapsed.asSeconds());
			speed.x*=brake;
			speed.y*=brake;
		}


		if(hotGunTime>0.0)
		{
			hotGunTime-=elapsed.asSeconds();
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				BulletSprite * pBS = (BulletSprite *) TPlayers::pBulletList->getPointerToNextInactive();
				if(pBS)
				{
					pBS->setPosition(position);
					pBS->isActive=true;
					float launchSpeed =600;
					pBS->setSpeedByAngle(rotation,launchSpeed);
					pBS->addSpeed(speed);
				}
				hotGunTime=startHotGunTime;
			}
			//multi-blast
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				int count=10;
				float angle=rotation;
				float angleInc = 360.0f/count;
				float launchSpeed =400.0f;
				for(int i=0;i<count;i++)
				{
					BulletSprite * pBS = (BulletSprite *) TPlayers::pBulletList->getPointerToNextInactive();
					if(!pBS)break;
					pBS->setPosition(position);
					pBS->isActive=true;
					pBS->setSpeedByAngle(angle,launchSpeed);
					pBS->addSpeed(speed);

					angle+=angleInc;
				}
				hotGunTime=startHotGunTime*5.0f;
			}
		}


		TSprite::update(elapsed);
	}


	virtual ~ShipSprite(void)
	{
	}

protected:

	float startHotGunTime;
	float hotGunTime;
};


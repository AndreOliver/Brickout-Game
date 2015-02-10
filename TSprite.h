#pragma once
#include "tgraphic.h"
#include "TGlobal.h"

class TSprite :
	public TGraphic
{
public:

	enum EdgeBehaviour {BOUNCE,WRAP,INACTIVATE,PREACTIVATE,BOUNCE_EXCEPT_BOTTOM,NONE};



	TSprite(void)
	{
		setScale(1.0f);

		setPosition(sf::Vector2f(0.0f,0.0f));
		setSpeed(sf::Vector2f(0.0f,0.0f));
		setAcceleration(sf::Vector2f(0.0f,0.0f));
		friction=0.0f;

		setRotation(0.0f);
		setRotationSpeed(0.0f);
		setRotationAcceleration(0.0f);

		setColor(sf::Color::White);
		setOpacity(255);
		gravity=0.0;
		isActive=true;
		edgeBehaviour = PREACTIVATE;
	}

	TSprite(string textureFileName)
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
	}

	void setFriction(float f)
	{
		friction=f;
	}
	void setGravity(float f)
	{
		gravity=f;
	}

	
	virtual void setColor(sf::Color c)
	{
		baseSprite.setColor(c);
	}

	virtual void setColor(int r,int g,int b,int a=255)
	{
		baseSprite.setColor(sf::Color(r,g,b,a));
	}

	virtual sf::Color getColor()
	{
		return baseSprite.getColor();
	}



	virtual void setOpacity(int op)
	{
		if(op<0)op=0;
		if(op>255)op=255;
		sf::Color c = baseSprite.getColor();
		c.a=op;
		baseSprite.setColor(c);
	}


	virtual int getOpacity()
	{
		return baseSprite.getColor().a;
	}


	virtual void setTexture(sf::Texture & texture)
	{
		baseSprite.setTexture(texture);
		textureSize = texture.getSize();
		baseSprite.setOrigin(textureSize.x/2.0f,textureSize.y/2.0f);
		collisionCircleRadius=sqrtf((float)(textureSize.x*textureSize.x+textureSize.y*textureSize.y));
	}

	virtual void setScale(sf::Vector2f newScale)
	{
		scale=newScale;
		baseSprite.setScale(scale);
	}

	virtual void setScale(float newScale)
	{
		scale.x=newScale;
		scale.y=newScale;
		baseSprite.setScale(scale);
	}

	virtual void setScale(float sx,float sy)
	{
		scale.x=sx;
		scale.y=sy;
		baseSprite.setScale(scale);
	}


	virtual float getScaleX()
	{
		return scale.x;
	}


	virtual void multiplyScaleBy(float m)
	{
		setScale(scale.x*m);
	}


	virtual void setRotation(float r)
	{
		rotation=r;
	}

	virtual void setRotationSpeed(float r)
	{
		rotation_speed=r;
	}


	virtual void setRotationAcceleration(float r)
	{
		rotation_acceleration=r;
	}

	virtual void setPosition(sf::Vector2f p)
	{
		position=p;
	}


	sf::Vector2f getPosition()
	{
		return position;
	}

	float getPositionX()
	{
		return position.x;
	}

	float getPositionY()
	{
		return position.y;
	}

	virtual void setPosition(float x,float y)
	{
		position.x=x;
		position.y=y;
	}

	virtual sf::Vector2f getSpeed()
	{
		return speed;
	}


	virtual float getAbsoluteSpeed()
	{
		return TGlobal::getVectorSize(speed);
	}

	virtual void setSpeed(sf::Vector2f s)
	{
		speed=s;
	}

	virtual void setSpeed(float x, float y)
	{
		speed.x=x;
		speed.y=y;
	}

	virtual void setSpeedByAngle(float angle,float speed)
	{
		setSpeed(sf::Vector2f(cosf((angle/180.0f)*3.1459f)*speed,sinf((angle/180.0f)*3.1459f)*speed));
	}

	virtual void addSpeed(sf::Vector2f av)
	{
		speed+=av;
	}



	virtual void setAcceleration(sf::Vector2f a)
	{
		acceleration=a;
	}


	virtual void update(sf::Time elapsed)
	{
		timeInState+=elapsed.asSeconds();
		if(isActive)
		{
			float elapsedSeconds=elapsed.asSeconds();
	
			acceleration.y+=gravity;

			speed+=acceleration*elapsedSeconds;

			speed*=1-(friction*elapsedSeconds);

			position+=speed*elapsedSeconds;

			rotation_speed+=rotation_acceleration*elapsedSeconds;
			rotation+=rotation_speed*elapsedSeconds;


			sf::Vector2u wSize = TGlobal::pMainWindow->getSize();

			switch(edgeBehaviour)
			{
				case BOUNCE:		

					if((position.x+(textureSize.x/2)*scale.x) > wSize.x)
					{
						speed.x=abs(speed.x)*-1;
					}
					else if((position.x-(textureSize.x/2)*scale.x) < 0)
					{
						speed.x=abs(speed.x);
					}

					if((position.y+(textureSize.y/2)*scale.y) > wSize.y  )
					{
						speed.y = abs( speed.y )*-1;
					}
			
					else if((position.y-(textureSize.y/2)*scale.y) < 0)
					{
						speed.y=abs(speed.y);
					}
				
					break;
				case BOUNCE_EXCEPT_BOTTOM:		

					if((position.x+(textureSize.x/2)*scale.x) > wSize.x)
					{
						speed.x=abs(speed.x)*-1;
					}
					else if((position.x-(textureSize.x/2)*scale.x) < 0)
					{
						speed.x=abs(speed.x);
					}


					if((position.y+(textureSize.y/2)*scale.y) > wSize.y  )
					{
						if(TGlobal::godMode)
						{
							speed.y = abs( speed.y )*-1;
						}
						else
						{
							isActive=false;
						}
					}



					if((position.y-(textureSize.y/2)*scale.y) < 0)
					{
						speed.y=abs(speed.y);
					}
				
					break;
				case INACTIVATE:

					if((position.x-(textureSize.x/2)*scale.x) > wSize.x) isActive=false;
					else if((position.x+(textureSize.x/2)*scale.x) < 0) isActive=false;

					if((position.y-(textureSize.y/2)*scale.y) > wSize.y  ) isActive=false;
					else if((position.y+(textureSize.y/2)*scale.y) < 0) isActive=false;
					break;
				case PREACTIVATE:
					if(
						((position.x-(textureSize.x/2)*scale.x) < wSize.x) &&
						((position.x+(textureSize.x/2)*scale.x) > 0) &&
						((position.y-(textureSize.y/2)*scale.y) < wSize.y  ) &&
						((position.y+(textureSize.y/2)*scale.y) > 0)
						)
					{
						edgeBehaviour=nextEdgeBehaviour;
					}
					break;
				case NONE:
					break;
			}

			baseSprite.setRotation(rotation);
			baseSprite.setPosition(position);
		}
	}

	virtual void draw(sf::RenderWindow & displayWindow)
	{
		if(isActive)
		{
			displayWindow.draw(baseSprite);
		}
	}

	float getScaledCollisionCircleRadius()
	{
		return collisionCircleRadius*scale.x;
	}

	virtual void hasCollidedWith(TSprite * pCollidedWith)
	{
	}

	float getHeight()
	{
		sf::FloatRect fr = baseSprite.getLocalBounds();
		return fr.height*scale.y;
	}

	float getWidth()
	{
		sf::FloatRect fr = baseSprite.getLocalBounds();
		return fr.width*scale.x;
	}

	virtual ~TSprite(void)
	{
	}

	void setEdgeBehaviour(EdgeBehaviour eb)
	{
		edgeBehaviour=eb;
	}


	void setNextEdgeBehaviour(EdgeBehaviour eb)
	{
		nextEdgeBehaviour=eb;
	}


	void changeState(int s)
	{
		firstTimeInState=true;
		timeInState=0.0f;
		state=s;
	}


protected:
	sf::Sprite baseSprite;

	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	float friction;
	float gravity;

	float rotation;
	float rotation_speed;
	float rotation_acceleration;

	sf::Vector2u textureSize;
	sf::Vector2f scale;

	EdgeBehaviour edgeBehaviour;
	EdgeBehaviour nextEdgeBehaviour;
	float collisionCircleRadius;

	int state;
	float timeInState;
	bool firstTimeInState;
};


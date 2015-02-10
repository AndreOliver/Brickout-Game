#pragma once
#include "tgraphic.h"
#include "TGame.h"



class TSpriteString :
	public TGraphic
{
public:


	TSpriteString(string fileName="persansb.ttf")
	{
		baseText.setFont(TGlobal::resources.getFont(fileName));
	}



	virtual void setText(string text)
	{
		baseText.setString(text);
	}


	virtual void setColor(sf::Color c)
	{
		baseText.setColor(c);
	}

	virtual void setOpacity(int op)
	{
		sf::Color c = baseText.getColor();
		c.a=op;
		baseText.setColor(c);
	}


	virtual void setFont(sf::Font & font)
	{
		baseText.setFont(font);
		baseText.setOrigin(0,0);
	}


	virtual void setPosition(sf::Vector2f p)
	{
		position=p;
	}

	virtual void setSpeed(sf::Vector2f s)
	{
		speed=s;
	}

	virtual void setAcceleration(sf::Vector2f a)
	{
		acceleration=a;
	}


	virtual void update(sf::Time elapsed)
	{
		if(isActive)
		{
			speed+=acceleration*elapsed.asSeconds();
			position+=speed*elapsed.asSeconds();
			if(bounce)
			{

				sf::Vector2u wSize = TGlobal::pMainWindow->getSize();

				if(position.x > wSize.x) speed.x=abs(speed.x)*-1;

				if( position.y > wSize.y  ) speed.y = abs( speed.y )*-1;
			
				if(position.x<0) speed.x=abs(speed.x);
			
				if(position.y<0) speed.y=abs(speed.y);
			}
			baseText.setPosition(position);
		}
	}

	virtual void draw(sf::RenderWindow & displayWindow)
	{
		displayWindow.draw(baseText);
	}

		virtual void setScale(sf::Vector2f newScale)
	{
		scale=newScale;
		baseText.setScale(scale);
	}

	virtual void setScale(float newScale)
	{
		scale.x=newScale;
		scale.y=newScale;
		baseText.setScale(scale);
	}

	virtual void setScale(float sx,float sy)
	{
		scale.x=sx;
		scale.y=sy;
		baseText.setScale(scale);
	}


	virtual ~TSpriteString(void)
	{
	}

protected:
	sf::Text baseText;
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	bool bounce;
};


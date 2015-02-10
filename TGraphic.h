#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
using namespace std;


class TGraphic
{
public:

	TGraphic(void)
	{
	}

	virtual void update(sf::Time elapsed)=0;

	virtual void draw(sf::RenderWindow & displayWindow)=0;	

	virtual void setColor(sf::Color c){}

	virtual void setOpacity(int op){}

	virtual void setTexture(sf::Texture & texture){}

	virtual	void setText(string text){}

	virtual void setScale(sf::Vector2f newScale){}

	virtual void setScale(float sx,float sy){}

	virtual void setScale(float newScale){}

	virtual void setIsActive(bool b=true)
	{
		isActive=b;
	}


	virtual void setPosition(sf::Vector2f p){}

	virtual void setPosition(float x,float y){}

	virtual void setSpeed(sf::Vector2f s){}

	virtual void setAcceleration(sf::Vector2f a){}

	

	virtual ~TGraphic(void)
	{
	}

public:

	sf::Vector2f scale;
	bool isActive;
	//int state;
};


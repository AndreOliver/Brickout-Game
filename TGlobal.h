#pragma once
#include "TResources.h"
#include "TGraphicList.h"


class TGlobal
{
public:

	TGlobal(void)
	{
	}

	virtual ~TGlobal(void)
	{
	}

	
	static float randomF()
	{
		return ((float)rand())/((float)RAND_MAX);
	}


	static float randomF(float max)
	{
		return randomF()*max;
	}


	static float randomF(float min,float max)
	{
		return randomF(max-min)+min;
	}

	static float randomAngle()
	{
		return randomF(360.0f);
	}
	
	static sf::Vector2f randVector2f(float minX,float maxX,float minY,float maxY)
	{
		return sf::Vector2f(randomF(minX,maxX),randomF(minY,maxY));
	}



	static int random(int max)
	{
		return rand()%max;
	}

	static int random(int min,int max)
	{
		return random(max-min)+min;
	}

	static sf::Color randomColor()
	{
		return sf::Color(rand()%256,rand()%256,rand()%256,255);
	}

	static sf::Color randomBrightColor()
	{
		return sf::Color(random(128,256),random(128,256),random(128,256),255);
	}

	static sf::Color randomizeColor(sf::Color c,int randFactor=40)
	{
		return sf::Color(squash(random(c.r-randFactor,c.r+randFactor)),squash(random(c.g-randFactor,c.g+randFactor)),squash(random(c.b-randFactor,c.b+randFactor)),255);
	}

	static int squash(int val,int min=0, int max=255)
	{
		if(val<min)return min;
		if(val>max)return max;
		return val;
	}



	static sf::Color randomChangeColor(sf::Color c,int randFactor)
	{
		return sf::Color(max(0,min(255,c.r+random(-randFactor,randFactor))),max(0,min(255,c.g+random(-randFactor,randFactor))),max(0,min(255,c.b+random(-randFactor,randFactor))),255);
	}

	static float getVectorSize(sf::Vector2f v)
	{
		return sqrtf(v.x*v.x+v.y*v.y);
	}

	static float getVectorAngle(sf::Vector2f v)
	{
		return (atan2f(v.y,v.x)*180.0f)/3.1459f;
	}

	static float distance(sf::Vector2f v1,sf::Vector2f v2)
	{
		return getVectorSize(v1-v2);
	}

	static bool isBetween(float val,float min,float max)
	{
		if ((val<min)||(val>max)) return false;
		return true;
	}

	static sf::RenderWindow * pMainWindow;
	static sf::Time elapsedTime;
	static TResources resources;
	static string newSceneName;
	static int ballsLeft;
	static int score;
	static float probabilityOfPowerUp;
	static bool godMode;

};


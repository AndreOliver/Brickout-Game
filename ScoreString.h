#pragma once
#include "tspritestring.h"
#include <string>
using namespace std;

class ScoreString :
	public TSpriteString
{
public:

	ScoreString(string fileName="persansb.ttf")
	{
		baseText.setFont(TGlobal::resources.getFont(fileName));
		position.x=30.0f;
		position.y=30.0f;
		isActive=true;
		setColor(sf::Color(255,255,255,255));
		setText("Hello");
	}

	virtual void update(sf::Time elapsed)
	{
		setText("Score: "+to_string(TGlobal::score));
		TSpriteString::update(elapsed);
	}

	virtual ~ScoreString(void)
	{
	}
};


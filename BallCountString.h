

#pragma once
#include "TSpriteString.h"
#include <string>
using namespace std;

class BallCountString :
	public TSpriteString
{
public:

	BallCountString(string fileName="persansb.ttf")
	{
		baseText.setFont(TGlobal::resources.getFont(fileName));
		position.x=(float)(TGlobal::pMainWindow->getSize().x-100);
		position.y=30.0f;
		isActive=true;
		setColor(sf::Color(255,255,255,255));
		setText("Hello");
	}

	virtual void update(sf::Time elapsed)
	{
		setText(to_string(TGlobal::ballsLeft));
		TSpriteString::update(elapsed);
	}

	virtual ~BallCountString(void)
	{
	}
};


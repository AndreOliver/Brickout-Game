#pragma once
#include "tgraphic.h"
#include <vector>
using namespace std;
class TGraphicList :
	public TGraphic
{
public:

	TGraphicList(void)
	{
		nextInactive=0;
	}

	virtual void update(sf::Time elapsed)
	{
		if(isActive)
		{
			for each (TGraphic * ptg in v)
			{
				if(ptg->isActive)ptg->update(elapsed);
			}
		}
	}

	virtual void draw(sf::RenderWindow & drawWindow)
	{
		if(isActive)
		{
			for each (TGraphic *  ptg in v)
			{
				if(ptg->isActive) ptg->draw(drawWindow);
			}
		}
	}

	virtual void setListItemsIsActive(bool b=true)
	{
		for each (TGraphic *  ptg in v)
		{
			ptg->isActive=b;
		}
	}



	virtual void add(TGraphic * ptg)
	{
		v.push_back(ptg);
	}


	virtual ~TGraphicList(void)
	{
	}

	vector<TGraphic *> & getVector()
	{
		return v;
	}

	int getSize()
	{
		return (int)(getVector().size());
	}

	int getActiveCount()
	{
		int result=0;
		for(int i=0;i<v.size();i++)
		{
			if(v[i]->isActive)result++;
		}
		return result;
	}

	TGraphic * getPointerToNextInactive()
	{
		for(int i=0;i<v.size();i++)
		{
			nextInactive++;
			if(nextInactive>=v.size())nextInactive=0;
			if(!(v[nextInactive]->isActive))
			{
				return v[nextInactive];
			}
		}
		return NULL;
	}

	TGraphic * getPointerToRandInactive()
	{
		nextInactive=rand()%v.size();
		return getPointerToNextInactive();
	}


	size_t size()
	{
		return v.size();
	}

	TGraphic * getPtrTGraphic(int i)
	{
		return v[i];
	}

private:
	int nextInactive;
	vector<TGraphic *> v;
};


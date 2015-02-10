#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include<map>
#include<string>
using namespace std;

class TResources
{
public:

	TResources(void)
	{
	}

	virtual ~TResources(void)
	{
		map<string,sf::SoundBuffer>::iterator iter;
		iter=soundBufferMap.begin();
		while(iter!=soundBufferMap.end())
		{
			
			iter++;
		}
	}



	sf::SoundBuffer & getSoundBuffer(string fileName)
	{
		if(soundBufferMap.find(fileName)==soundBufferMap.end())
		{
			//texture not loaded
			sf::SoundBuffer newSB;
			if(newSB.loadFromFile("..\\Resources\\"+fileName))
			{
				soundBufferMap[fileName]=newSB;
			}
			else
			{
				throw (string)"Error: "+fileName+" not found in resource directory.";
			}
		}
		return soundBufferMap[fileName];
	}


	sf::Font & getFont(string fileName)
	{
		if(fontMap.find(fileName)==fontMap.end())
		{
			//texture not loaded
			sf::Font newFont;
			if(newFont.loadFromFile("..\\Resources\\"+fileName))
			{
				fontMap[fileName]=newFont;
			}
			else
			{
				throw (string)"Error: "+fileName+" not found in resource directory.";
			}
		}
		return fontMap[fileName];
	}


	sf::Texture & getTexture(string fileName)
	{
		if(textureMap.find(fileName)==textureMap.end())
		{
			//texture not loaded
			sf::Texture newTexture;
			if(newTexture.loadFromFile("..\\Resources\\"+fileName))
			{
				textureMap[fileName]=newTexture;
			}
			else
			{
				throw (string)"Error: "+fileName+" not found in resource directory.";
			}
		}
		return textureMap[fileName];
	}

private:
	map<string,sf::Texture> textureMap;
	map<string,sf::Font> fontMap;
	map<string,sf::SoundBuffer> soundBufferMap;
};


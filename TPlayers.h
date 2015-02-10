#pragma once

class BrickSprite;
class ShipSprite;
class BallSprite;
class PaddleSprite;
class TGraphicList;
class TSprite;
class TSpriteString;
class ScoreString;
class BallCountString;
class BallCountDisplay;
class PowerUpSprite;
class StickyPaddlePowerUp;
class SuperBallPowerUp;

class TPlayers
{
public:

	TPlayers(void)
	{
	}

	virtual ~TPlayers(void)
	{
	}

	static void setup();
	static void colisionCheck(TGraphicList * pTGL1,TGraphicList * pTGL2);


	static float distance(TSprite * pS1,TSprite * pS2);




	static PaddleSprite * pPaddle;
	static ShipSprite   * pShip;
	static BallSprite   * pBall;
	static TGraphicList * pBallList;
	static TGraphicList * pBrickList;
	static TGraphicList * pBulletList;
	static TGraphicList * pCrystalList;
	static TGraphicList * pExploList;
	static TGraphicList * pParticleList;
	static ScoreString * pScoreString;
	static BallCountString * pBallCountString;
	static BallCountDisplay * pBallCountDisplay;
	static TGraphicList * pPowerUpList;
	static TSpriteString * pDebugString; 
};


#pragma once
#include "ImageObject.h"

class PsylhaEngine;

class Player :
	public ImageObject
{
public:
	Player(PsylhaEngine* pEngine);
	~Player();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	//SimpleImage getImage() { return image; }
private:
	PsylhaEngine* m_pEngine;
	std::string fp;
	SimpleImage image;

	bool dir;
	bool sprintFlag;
	int health;
	int startTime;
	int time;
	bool timeFlag;
public:
	void virtMouseDown(int iButton, int iX, int iY);
	void virtKeyDown(int iKeyCode);
};


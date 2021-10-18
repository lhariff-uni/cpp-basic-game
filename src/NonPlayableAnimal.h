#pragma once
#include "ImageObject.h"
#include "MovementPosition.h"

class PsylhaEngine;

class NonPlayableAnimal :
	public ImageObject
{
public:
	NonPlayableAnimal(PsylhaEngine* pEngine);
	~NonPlayableAnimal();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
private:
	PsylhaEngine* m_pEngine;
	std::string fp;
	SimpleImage image;

	MovementPosition mov;
	bool dir;
	bool colFlag;
};

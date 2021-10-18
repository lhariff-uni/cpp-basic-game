#include "header.h"
#include "NonPlayableAnimal.h"
#include "CollisionDetection.h"
#include "PsylhaEngine.h"

const std::string folder = "panda/";
NonPlayableAnimal::NonPlayableAnimal(PsylhaEngine* pEngine)
	:ImageObject(500,400,pEngine, "panda/faceLeft1.png")
{
	m_pEngine = pEngine;
	fp = "faceLeft";
	dir = false;
	image = ImageManager::loadImage(folder + fp + "1.png", true);
	m_iDrawHeight = image.getHeight();
	m_iDrawWidth = image.getWidth();
	m_iStartDrawPosX = true ? 0 : -m_iDrawWidth / 2;
	m_iStartDrawPosY = true ? 0 : -m_iDrawHeight / 2;
	colFlag = false;
	mov.setup(
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		5,
		5 + 1000);

	setVisible(true);
}
NonPlayableAnimal::~NonPlayableAnimal() {

}

void NonPlayableAnimal::virtDraw() {
	if (!isVisible())
		return;

	int iTick = getEngine()->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 30;
	if (fp.find("face") == 0) {
		if (iFrame % 8 == 0)
			image = ImageManager::loadImage(folder + fp + "1.png", true);
		else if (iFrame % 8 == 1)
			image = ImageManager::loadImage(folder + fp + "2.png", true);
		else if (iFrame % 8 == 2)
			image = ImageManager::loadImage(folder + fp + "3.png", true);
		else if (iFrame % 8 == 3)
			image = ImageManager::loadImage(folder + fp + "4.png", true);
		else if (iFrame % 8 == 4)
			image = ImageManager::loadImage(folder + fp + "5.png", true);
		else if (iFrame % 8 == 5)
			image = ImageManager::loadImage(folder + fp + "6.png", true);
		else if (iFrame % 8 == 6)
			image = ImageManager::loadImage(folder + fp + "7.png", true);
		else if (iFrame % 8 == 7)
			image = ImageManager::loadImage(folder + fp + "8.png", true);
		m_iDrawHeight = image.getHeight();
		m_iDrawWidth = image.getWidth();
	}
	else if (fp.find("play") == 0) {
		if (iFrame % 3 == 0)
			image = ImageManager::loadImage(folder + fp + "1.png", true);
		else if (iFrame % 3 == 1)
			image = ImageManager::loadImage(folder + fp + "2.png", true);
		else if (iFrame % 3 == 2)
			image = ImageManager::loadImage(folder + fp + "3.png", true);
		m_iDrawHeight = image.getHeight();
		m_iDrawWidth = image.getWidth();
	}
	else if (fp.find("walk") == 0) {
		if (iFrame % 3 == 0)
			image = ImageManager::loadImage(folder + fp + "1.png", true);
		else if (iFrame % 3 == 1)
			image = ImageManager::loadImage(folder + fp + "2.png", true);
		else if (iFrame % 3 == 2)
			image = ImageManager::loadImage(folder + fp + "3.png", true);
		m_iDrawHeight = image.getHeight();
		m_iDrawWidth = image.getWidth();
	}
	else if (fp.find("eat") == 0) {
		if (iFrame % 13 == 0)
			image = ImageManager::loadImage(folder + fp + "1.png", true);
		else if (iFrame % 11 == 1)
			image = ImageManager::loadImage(folder + fp + "2.png", true);
		else if (iFrame % 11 == 2)
			image = ImageManager::loadImage(folder + fp + "3.png", true);
		else if (iFrame % 11 == 3)
			image = ImageManager::loadImage(folder + fp + "4.png", true);
		else if (iFrame % 11 == 4)
			image = ImageManager::loadImage(folder + fp + "5.png", true);
		else if (iFrame % 11 == 5)
			image = ImageManager::loadImage(folder + fp + "6.png", true);
		else if (iFrame % 11 == 6)
			image = ImageManager::loadImage(folder + fp + "7.png", true);
		else if (iFrame % 11 == 7)
			image = ImageManager::loadImage(folder + fp + "8.png", true);
		else if (iFrame % 11 == 8)
			image = ImageManager::loadImage(folder + fp + "9.png", true);
		else if (iFrame % 11 == 9)
			image = ImageManager::loadImage(folder + fp + "10.png", true);
		else if (iFrame % 11 == 10)
			image = ImageManager::loadImage(folder + fp + "11.png", true);
		m_iDrawHeight = image.getHeight();
		m_iDrawWidth = image.getWidth();
	}
	else if (fp.find("sit") == 0) {
		image = ImageManager::loadImage(folder + fp + ".png", true);
		m_iDrawHeight = image.getHeight();
		m_iDrawWidth = image.getWidth();
	}

	image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
		m_iCurrentScreenX + m_iStartDrawPosX,
		m_iCurrentScreenY + m_iStartDrawPosY,
		m_iDrawWidth, m_iDrawHeight,
		0x000000);
}

void NonPlayableAnimal::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible() || getEngine()->isPaused())
		return;
	
	//Requirement 10: Two moving-objects interact
	DisplayableObject* pObject = m_pEngine->getDisplayableObject(1);
	int x1l = pObject->getXCentre() - pObject->getDrawWidth() / 2,
		x1r = pObject->getXCentre() + pObject->getDrawWidth() / 2,
		y1t = pObject->getYCentre(), //shorten collision box
		y1b = pObject->getYCentre() + pObject->getDrawHeight() / 2;
	if (
		CollisionDetection::checkRectangles(
			x1l, x1r, y1t, y1b,
			m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
			m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight)
		&&
		!colFlag
		)
	{ 
		colFlag = true;
		std::cout << "touching" << std::endl;
		int temp = rand() % 500 + 1;	
		mov.setup(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth / 2 > pObject->getXCentre() ? 
			m_iCurrentScreenX + temp : m_iCurrentScreenX - temp,
			m_iCurrentScreenY + m_iDrawHeight / 2 > pObject->getYCentre() ?
			m_iCurrentScreenY + (500 - temp) : m_iCurrentScreenY - (500 - temp),
			iCurrentTime,
			iCurrentTime + 500 + rand() % 100);
		mov.calculate(iCurrentTime + 500); //get direction
		dir = m_iCurrentScreenX < mov.getX();
		fp = dir ? "walkRight" : "walkLeft";
	}
	
	//Requirement 5: Movement Automation
	if (mov.hasMovementFinished(iCurrentTime))
	{
		colFlag = false;
		int tempX = 0, tempY = 0;
		int diffX = 0, diffY = 0;
		switch (rand() % 15) {
		case 0: 
			fp = dir ? "faceRight" : "faceLeft";
			break;
		case 1: 
			fp = dir ? "playRight" : "playLeft";
			break;
		case 2: 
			fp = dir ? "eatRight" : "eatLeft";
			break;
		case 3: 
			fp = dir ? "sitRight" : "sitLeft";
			break;
		default:
			tempX = rand() % (m_iCurrentScreenX - 150) + 300;
			tempY = rand() % (m_iCurrentScreenY - 50) + 100;
			diffX = tempX > m_iDrawHeight ? tempX - m_iDrawHeight : m_iDrawHeight - tempX;
			diffY = tempY > m_iDrawWidth ? tempY - m_iDrawWidth : m_iDrawWidth - tempY;
			mov.setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				tempX,
				tempY,
				iCurrentTime,
				iCurrentTime + 1000 + (diffX + diffY));
			mov.calculate(iCurrentTime + 1000); //used to get direction
			dir = m_iCurrentScreenX < mov.getX();
			fp = dir ? "walkRight" : "walkLeft";
			break;
		}
		if (fp.find("walk") != 0) {
			mov.setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				iCurrentTime,
				iCurrentTime + 5000 + rand() % 10000);
		}
	}
	mov.calculate(iCurrentTime); //used for movement
	m_iCurrentScreenX = mov.getX();
	m_iCurrentScreenY = mov.getY();

	/*
	if (getEngine()->isKeyPressed(SDLK_z)) {
		fp = "eatLeft";
		dir = false;
	}
	else if (getEngine()->isKeyPressed(SDLK_x)) {
		fp = "sitLeft";
		dir = false;
	}
	else if (getEngine()->isKeyPressed(SDLK_c)) {
		fp = "playLeft";
		dir = false;
	}
	else if (getEngine()->isKeyPressed(SDLK_v)) {
		fp = "faceLeft";
		dir = false;
	}
	*/

	if (m_iCurrentScreenX + m_iDrawWidth < 0 && !dir) {
		m_iCurrentScreenX = getEngine()->getWindowWidth();
	}
	if (m_iCurrentScreenX > getEngine()->getWindowWidth() && dir) {
		m_iCurrentScreenX = 0 - m_iDrawWidth;
	}

	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
	this->redrawDisplay();
}
#include "header.h"
#include "MyObjectA.h"
#include "BaseEngine.h"

MyObjectA::MyObjectA(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	m_iCurrentScreenX = 100; // Starting position on the screen
	m_iCurrentScreenY = 200;
	m_iDrawWidth = 100; // Width of drawing area
	m_iDrawHeight = 200; // Height of drawing area
}
MyObjectA::~MyObjectA()
{

}

void MyObjectA::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
}


void MyObjectA::virtDoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 2;
	if (getEngine()->isKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 2;
	
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();

}

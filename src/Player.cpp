#include "header.h"
#include "Player.h"
#include "PsylhaEngine.h"
#include "CollisionDetection.h"

const std::string folder = "player/";
Player::Player(PsylhaEngine* pEngine)
	: ImageObject(200,100,pEngine,"player/faceLeft1.png")
{
	fp = "faceLeft";
	image = ImageManager::loadImage(folder + fp + "1.png", true);
	m_iDrawHeight = image.getHeight();
	m_iDrawWidth = image.getWidth();
	m_iStartDrawPosX = true ? 0 : -m_iDrawWidth / 2;
	m_iStartDrawPosY = true ? 0 : -m_iDrawHeight / 2;
	dir = false;
	sprintFlag = false;
	health = 10;
	time = 0;
	timeFlag = false;

	m_pEngine = pEngine;
	setVisible(true);
}


Player::~Player()
{
}


void Player::virtDraw()
{
	if (isVisible())
	{
		int iTick = getEngine()->getModifiedTime() / 100; // 1 per 100ms
		int iFrame = iTick % 30;
		if (fp.find("face") == 0) {
			if (iFrame % 4 == 0) 
				image = ImageManager::loadImage(folder + fp + "1.png", true);
			else if (iFrame % 4 == 1) 
				image = ImageManager::loadImage(folder + fp + "2.png", true);
			else if (iFrame % 4 == 2) 
				image = ImageManager::loadImage(folder + fp + "3.png", true);
			else if (iFrame % 4 == 3) 
				image = ImageManager::loadImage(folder + fp + "4.png", true);
			if (m_iDrawHeight < m_iDrawWidth) {
				m_iCurrentScreenY -= m_iDrawHeight / 2 + 65;
				m_iDrawHeight = image.getHeight();
				m_iDrawWidth = image.getWidth();
			}
		}
		else if (fp.find("walk") == 0) {
			if (iFrame % 5 == 0)
				image = ImageManager::loadImage(folder + fp + "1.png", true);
			else if (iFrame % 5 == 1)
				image = ImageManager::loadImage(folder + fp + "2.png", true);
			else if (iFrame % 5 == 2)
				image = ImageManager::loadImage(folder + fp + "3.png", true);
			else if (iFrame % 5 == 3)
				image = ImageManager::loadImage(folder + fp + "4.png", true);
			else if (iFrame % 5 == 4)
				image = ImageManager::loadImage(folder + fp + "5.png", true);
			if (m_iDrawHeight < m_iDrawWidth) {
				m_iCurrentScreenY -= m_iDrawHeight / 2 + 65;
				m_iDrawHeight = image.getHeight();
				m_iDrawWidth = image.getWidth();
			}
		}
		else if (fp.find("prone") == 0) {
			image = ImageManager::loadImage(folder + fp + ".png", true);
			if (m_iDrawHeight > m_iDrawWidth) {
				m_iCurrentScreenY += m_iDrawHeight / 2;
			}
			m_iDrawHeight = image.getHeight();
			m_iDrawWidth = image.getWidth();
			
		}
		//Requirement 2: Drawn shapes to foreground
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX - 5, m_iCurrentScreenY - 10,
			m_iCurrentScreenX + 30, m_iCurrentScreenY + 15,
			0x000000);

		//Requirement 7: Foreground, moving text
		getEngine()->drawForegroundString(
			m_iCurrentScreenX,
			m_iCurrentScreenY + m_iStartDrawPosY - 10, 
			(std::to_string(health)).c_str(), 
			0xff0000, NULL);
		getEngine()->drawForegroundString(
			getEngine()->getWindowWidth() / 2 - 50,
			getEngine()->getWindowHeight() - 50,
			(std::to_string(time)).c_str(),
			0xffff00, NULL);

		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, 
			m_iCurrentScreenX + m_iStartDrawPosX, 
			m_iCurrentScreenY + m_iStartDrawPosY, 
			m_iDrawWidth, m_iDrawHeight, 
			0x000000);
	}
}

void Player::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible() || getEngine()->isPaused())
		return;

	if (dir) {
		fp = "faceRight";
	}
	else {
		fp = "faceLeft";
	}

	//Requirement 3 & 4: User-controlled and input-handling
	if (getEngine()->isKeyPressed(SDLK_LSHIFT) || getEngine()->isKeyPressed(SDLK_RSHIFT)) {
		if (dir)
			fp = "proneRight";
		else
			fp = "proneLeft";
	}
	else {
		if (getEngine()->isKeyPressed(SDLK_LEFT)) {
			m_iCurrentScreenX -= sprintFlag ? 12 : 6;
			fp = "walkLeft";
			dir = false;
		}
		if (getEngine()->isKeyPressed(SDLK_RIGHT)) {
			m_iCurrentScreenX += sprintFlag ? 12 : 6;
			fp = "walkRight";
			dir = true;
		}
		if (getEngine()->isKeyPressed(SDLK_UP)) {
			m_iCurrentScreenY -= sprintFlag ? 12 : 6;
			if (dir)
				fp = "walkRight";
			else
				fp = "walkLeft";
		}
		if (getEngine()->isKeyPressed(SDLK_DOWN)) {
			m_iCurrentScreenY += sprintFlag ? 12 : 6;
			if (dir)
				fp = "walkRight";
			else
				fp = "walkLeft";
		}
		if (getEngine()->isKeyPressed(SDLK_LCTRL) || getEngine()->isKeyPressed(SDLK_RCTRL)) {
			sprintFlag = true;
		}
		else {
			sprintFlag = false;
		}
	}

	//Requirement 9: Object interacts with tiles
	PsylhaTileManager& tm = m_pEngine->getTileManager();
	if (timeFlag) {
		timeFlag = true;

		//Requirement 7: Text changes every 100ms
		time = getEngine()->getModifiedTime() / 100 - startTime;
	}
	if (tm.isValidTilePosition(m_iCurrentScreenX+m_iDrawWidth/2, m_iCurrentScreenY+m_iDrawHeight/2)) {
		int iMapX = tm.getMapXForScreenX(m_iCurrentScreenX + m_iDrawWidth / 2), 
			iMapY = tm.getMapYForScreenY(m_iCurrentScreenY + m_iDrawHeight);
		int iMapVal = tm.getMapValue(iMapX, iMapY);
		if (dir) {
			if ((iMapVal == 3 || iMapVal == 4)) {
				for (int x = 0; x < 2; x++) {
					for (int y = 0; y < 14; y++) {
						tm.setAndRedrawMapValueAt(x, y, tm.getMapValue(x, y) + 4,
							getEngine(), getEngine()->getBackgroundSurface());
					}
				}
				timeFlag = true;
				startTime = getEngine()->getModifiedTime() / 100;
			}
			else if ((iMapVal == 5 || iMapVal == 6)) {
				for (int x = 0; x < 2; x++) {
					for (int y = 0; y < 14; y++) {
						tm.setAndRedrawMapValueAt(x, y, tm.getMapValue(x, y) + 4,
							getEngine(), getEngine()->getBackgroundSurface());
					}
				}
				timeFlag = false;
			}
		}
		else {
			if ((iMapVal == 1 || iMapVal == 2)) {
				for (int x = 0; x < 2; x++) {
					for (int y = 0; y < 14; y++) {
						tm.setAndRedrawMapValueAt(x, y, tm.getMapValue(x, y) + 4,
							getEngine(), getEngine()->getBackgroundSurface());
					}
				}
				timeFlag = true;
				startTime = getEngine()->getModifiedTime() / 100;
			}
			else if ((iMapVal == 7 || iMapVal == 8)) {
				for (int x = 0; x < 2; x++) {
					for (int y = 0; y < 14; y++) {
						tm.setAndRedrawMapValueAt(x, y, tm.getMapValue(x, y) + 4,
							getEngine(), getEngine()->getBackgroundSurface());
					}
				}
				timeFlag = false;	
			}
		}
	}

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

void Player::virtKeyDown(int iKeyCode) 
{
}

//Requirement 4: Handling mouse-clicks
void Player::virtMouseDown(int iButton, int iX, int iY)
{
	PsylhaTileManager&tm = m_pEngine->getTileManager();
	if (tm.isValidTilePosition(iX, iY)) {
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 14; y++) {
				if (tm.getMapValue(x, y) > 4) {
					tm.setAndRedrawMapValueAt(x, y, tm.getMapValue(x, y) - 8,
						getEngine(), getEngine()->getBackgroundSurface());
				}
			}
		}
		time = 0;
	}
}

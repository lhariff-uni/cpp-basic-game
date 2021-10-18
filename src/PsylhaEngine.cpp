#include "header.h"
#include "BaseEngine.h"
#include "PsylhaEngine.h"
#include "Player.h"
#include "NonPlayableAnimal.h"
#include "TileManager.h"

PsylhaEngine::PsylhaEngine()
{
	notifyObjectsAboutKeys(true);
	notifyObjectsAboutMouse(true);
}
PsylhaEngine::~PsylhaEngine() {

}

void PsylhaEngine::virtSetupBackgroundBuffer()
{
	//Requirement 1: Engine and Background
	fillBackground(0x46792d);
	for (int iX = 0; iX < getWindowWidth(); iX += 5) {
		int colour = 0;
		for (int iY = 0; iY < this->getWindowHeight(); iY += 5) {
			int r = rand() % 6;
			if(r == 0)
				colour = 0x46792d;
			else if (r == 1)
				colour = 0x46772c;
			else if (r == 2)
				colour = 0x45752a;
			else if (r == 3)
				colour = 0x4e8530;
			else if (r == 4)
				colour = 0x477b2d;
			else if (r == 5)
				colour = 0x43722a;
			//Requirement 2: Drawn shapes to background
			drawBackgroundRectangle(iX, iY, iX + 4, iY + 4, colour);
		}
	}

	//Requirement 8: Tile Manager Implementation
	const char* data[] = {
				"cd",
				"be",
				"cd",
				"be",
				"cd",
				"be",
				"cd",
				"be",
				"cd",
				"be",
				"cd",
				"be",
				"cd",
				"be"
	};
	tm.setMapSize(2, 14);
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 14; y++) {
			tm.setMapValue(x, y, data[y][x] - 'a');
		}
	}
	tm.setTopLeftPositionOnScreen(getWindowWidth()/2-tm.getTileWidth(), 50);
	tm.drawAllTiles(this, this->getBackgroundSurface());

	//Requirement 6: Text to background
	drawBackgroundString(0, 0, "Hold SHIFT to prone", 0xff0000, NULL);
}


int PsylhaEngine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);

	createObjectArray(2);
	storeObjectInArray(0, new NonPlayableAnimal(this));
	storeObjectInArray(1, new Player(this));

	setAllObjectsVisible(true);
	return 0;
}

void PsylhaEngine::virtDrawStringsUnderneath()
{
}

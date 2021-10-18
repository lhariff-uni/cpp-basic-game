#include "header.h"
#include "PsylhaTileManager.h"

PsylhaTileManager::PsylhaTileManager()
	: TileManager(50, 50)
{
}

PsylhaTileManager::~PsylhaTileManager()
{
}

void PsylhaTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	switch (getMapValue(iMapX, iMapY))
	{
	case 0:
		break;
	case 1:
	case 3:
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0x000000);
		break;
	case 2:
	case 4:
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0xffffff);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0x00ff00);
		break;
	case 9:
	case 10:
	case 11:
	case 12:
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0xff0000);
		break;
	}
}
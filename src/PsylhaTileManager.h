#pragma once
#include "TileManager.h"

class PsylhaTileManager :
	public TileManager
{
public:
	PsylhaTileManager();
	~PsylhaTileManager();

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
};


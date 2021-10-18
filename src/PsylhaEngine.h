#pragma once
#include "BaseEngine.h"
#include "PsylhaTileManager.h"
class PsylhaEngine :
	public BaseEngine
{
public:
	PsylhaEngine();
	~PsylhaEngine();
	void virtSetupBackgroundBuffer() override;
	int virtInitialiseObjects() override;
	void virtDrawStringsUnderneath() override;
	PsylhaTileManager& getTileManager() { return tm; }
private:
	PsylhaTileManager tm;
};
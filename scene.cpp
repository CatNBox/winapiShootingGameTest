#include "gameMetaData.h"
#include "scene.h"

scene::scene()
{
	currUIState = gameSysData::uiState::idle;
}

scene::~scene()
{
}

gameSysData::uiState scene::getUIState()
{
	return currUIState;
}

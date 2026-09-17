#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
#include "uiPauseBtn.h"
#include "uiPauseMenu.h"

uiPauseMenu::uiPauseMenu(HDC rcvDC)
	:gameObject(galagaResource::imgAddrTest, rcvDC)
{
	initPos(0, 0);
	pauseBtn = (gameObject*)(new uiPauseBtn(rcvDC));
}

uiPauseMenu::~uiPauseMenu()
{
}

void uiPauseMenu::initParam()
{
	currState = gameSysData::uiState::idle;
	((uiPauseBtn*)pauseBtn)->initParam();
}

void uiPauseMenu::update()
{
	pauseBtn->update();
	currState = ((uiPauseBtn*)pauseBtn)->getState();
}

void uiPauseMenu::draw()
{
	gameObject::draw();
	pauseBtn->draw();
}

gameSysData::uiState uiPauseMenu::getState()
{
	return currState;
}

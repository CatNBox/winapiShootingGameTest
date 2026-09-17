#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
#include "uiPauseBtn.h"

uiPauseBtn::uiPauseBtn(HDC rcvDC)
	:gameObject(galagaResource::imgAddrPauseBtnOnReturn, rcvDC)
{
	initPos(232, 300);
	currState = gameSysData::uiState::return2Game;
}

uiPauseBtn::~uiPauseBtn()
{
}

void uiPauseBtn::initParam()
{
	currState = gameSysData::uiState::idle;
}

void uiPauseBtn::update()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		graphicResourceAddress = galagaResource::imgAddrPauseBtnOnExit;
		initSprite();
		currState = gameSysData::uiState::onExit;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		graphicResourceAddress = galagaResource::imgAddrPauseBtnOnReturn;
		initSprite();
		currState = gameSysData::uiState::return2Game;
	}
}

void uiPauseBtn::draw()
{
	gameObject::draw();
}

gameSysData::uiState uiPauseBtn::getState()
{
	return currState;
}

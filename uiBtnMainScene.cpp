// 메타 데이터
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
// 클래스 헤더
#include "uiBtnMainScene.h"

uiBtnMainScene::uiBtnMainScene(HDC rcvDC)
	:gameObject(galagaResource::imgAddrMainBtnOnGameStart2, rcvDC)
{
	initPos(565, 385);
	currState = gameSysData::uiState::onGameStart;
}

uiBtnMainScene::~uiBtnMainScene()
{
}

void uiBtnMainScene::update()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		graphicResourceAddress = galagaResource::imgAddrMainBtnOnExit2;
		initSprite();
		currState = gameSysData::uiState::onExit;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		graphicResourceAddress = galagaResource::imgAddrMainBtnOnGameStart2;
		initSprite();
		currState = gameSysData::uiState::onGameStart;
	}
}

void uiBtnMainScene::draw()
{
	gameObject::draw();
}

gameSysData::uiState uiBtnMainScene::getState()
{
	return currState;
}

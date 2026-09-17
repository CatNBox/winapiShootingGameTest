// gameObjects
#include "mainSceneBG.h"
#include "uiBtnMainScene.h"
#include "gameMetaData.h"
// class header
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
	delete backGround;
	delete uiBtnSet;
}

void mainScene::initScene(HDC hdc)
{
	// init objects and background
	backGround = (gameObject*)(new mainSceneBG(hdc));
	uiBtnSet = (gameObject*)(new uiBtnMainScene(hdc));
}

void mainScene::initParam()
{
	currUIState = gameSysData::uiState::idle;
}

void mainScene::update()
{
	input();
	uiBtnSet->update();
}

void mainScene::draw()
{
	backGround->draw();
	uiBtnSet->draw();
}

void mainScene::input()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		auto currBtnState = ((uiBtnMainScene*)uiBtnSet)->getState();
		if (currBtnState == gameSysData::uiState::onExit)
		{
			ExitProcess(TRUE);
		}
		if (currBtnState == gameSysData::uiState::onGameStart)
		{
			currUIState = gameSysData::uiState::gameStart;
		}
	}
}

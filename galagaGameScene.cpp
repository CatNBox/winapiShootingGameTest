// metaData
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
// gameObjects
#include "gameObject.h"
#include "galagaBG.h"
#include "galagaFighter.h"
#include "bossGalaga.h"
#include "bullet.h"
#include "bulletPool.h"
#include "galagaling.h"
#include "enemyPool.h"
#include "uiScore.h"
#include "uiPauseMenu.h"
// class header
#include "galagaGameScene.h"

galagaGameScene::galagaGameScene()
{
}

galagaGameScene::~galagaGameScene()
{
	delete uiPauseObj;
	delete uiScoreObj;
	delete boss01;
	delete player;
	delete backGround;
	delete enemies;
	delete bullets;
}

void galagaGameScene::initScene(HDC hdc)
{
	// init objects and background
	bullets = new bulletPool;
	bullets->initPool(hdc);
	enemies = new enemyPool;
	enemies->initPool(hdc, bullets);
	enemyGenerateCoolTime = galagaData::stage1GenerateCooltimeNormal;	// 임시값
	backGround = (gameObject*)(new galagaBG(hdc));
	player = (gameObject*)(new galagaFighter(hdc, bullets));
	boss01 = (gameObject*)(new bossGalaga(hdc));
	uiScoreObj = (gameObject*)(new uiScore(hdc));
	uiPauseObj = (gameObject*)(new uiPauseMenu(hdc));

	gameStartDelay = -1;
	gamePauseFlag = false;
	keyInputDelay = 320;
	keyTrigger = false;
}

void galagaGameScene::initParam()
{
	currUIState = gameSysData::uiState::idle;

	//클린 오브젝트
}

void galagaGameScene::update()
{
	input();

	if (gamePauseFlag == false)
	{
		player->update();
		//boss01->update();
		bullets->update();
		if (enemyGenerateCoolTime < 0)
		{
			int randType = 3 + rand() % 3;
			int randInitX = 50 + 100 * (rand() % 10);
			int enemyInitY = 0;
			enemies->create(galagaData::galagaling::bodyType(randType), randInitX, enemyInitY);
			if (uiScoreObj->getScore() < 500)
			{
				enemyGenerateCoolTime = galagaData::stage1GenerateCooltimeNormal;
			}
			else if (uiScoreObj->getScore() < 1000)
			{
				enemyGenerateCoolTime = galagaData::stage1GenerateCooltimeHard;
			}
			else if (uiScoreObj->getScore() >= 1000)
			{
				enemyGenerateCoolTime = galagaData::stage1GenerateCooltimeLast;
			}
			else if (uiScoreObj->getScore() > 5000)
			{
				// 보스전
			}
		}
		else
		{
			enemyGenerateCoolTime -= gameSysData::baseGameTick;
		}
		enemies->update();
		uiScoreObj->update();
	}
	else
	{
		uiPauseObj->update();
	}
}

void galagaGameScene::draw()
{
	backGround->draw();
	player->draw();
	//boss01->draw();
	bullets->draw();
	enemies->draw();
	uiScoreObj->draw();
	if (gamePauseFlag == true)
	{
		uiPauseObj->draw();
	}
}

void galagaGameScene::input()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (keyTrigger == false)
		{
			keyTrigger = true;
			keyInputDelay = 320;
			togglePause();
		}
	}
	if (gamePauseFlag == true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			auto currBtnState = ((uiPauseMenu*)uiPauseObj)->getState();
			if (currBtnState == gameSysData::uiState::onExit)
			{
				/*currUIState = gameSysData::uiState::return2Title;
				((uiPauseMenu*)uiPauseObj)->initParam();
				togglePause();*/
				ExitProcess(TRUE);
			}
			if (currBtnState == gameSysData::uiState::return2Game)
			{
				togglePause();
			}
		}
	}
	
	if (keyInputDelay > 0)
	{
		keyInputDelay -= gameSysData::baseGameTick;
	}
	else
	{
		keyTrigger = false;
	}
}

void galagaGameScene::togglePause()
{
	gamePauseFlag = !gamePauseFlag;
}

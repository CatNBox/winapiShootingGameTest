#include "sprites.h"
#include "scene.h"
#include "mainScene.h"
#include "galagaGameScene.h"
#include "gameMetaData.h"
#include "gameFramework.h"

gameFramework::gameFramework()
{
	// init screen base
	baseScreenHandle = new sprites::spriteHandle;
	
	// init related tick
	msPerUpdate = gameSysData::baseGameTick;
	prevTick = GetTickCount();
	lag = 0.0;

}

gameFramework::~gameFramework()
{
	delete baseScreenHandle;
}

void gameFramework::gameLoop(HDC hdc)
{
	double currTick = GetTickCount();
	double elapsed = currTick - prevTick;
	prevTick = currTick;
	lag += elapsed;

	while (lag >= msPerUpdate)
	{
		update();
		lag -= msPerUpdate;
	}
	drawScreen(hdc);
}

void gameFramework::drawScreen(HDC hdc)
{
	currScene->draw();
	
	//base ->g_hdc
	//베이스의 dc를 화면 dc에직는다 
	BitBlt(hdc, 0, 0, baseScreenHandle->bit.bmWidth, baseScreenHandle->bit.bmHeight,
		baseScreenHandle->dc, 0, 0, SRCCOPY);
}

void gameFramework::update()
{
	currScene->update();
	if (currScene->getUIState() == gameSysData::uiState::gameStart)
	{
		currScene = gameSceneObj;
		((mainScene*)mainSceneObj)->initParam();
	}
	else if (currScene->getUIState() == gameSysData::uiState::return2Title)
	{
		currScene = mainSceneObj;
		((galagaGameScene*)gameSceneObj)->initParam();
	}
}

void gameFramework::initScene()
{
	mainSceneObj = (scene*)(new mainScene);
	mainSceneObj->initScene(baseScreenHandle->dc);
	gameSceneObj = (scene*)(new galagaGameScene);
	gameSceneObj->initScene(baseScreenHandle->dc);

	// 시작 씬 세팅
	currScene = mainSceneObj;
}

// call by WM_CREATE
void gameFramework::initScreen(HDC hdc)
{
	baseScreenHandle->hBmp = (HBITMAP)LoadImage(NULL, L"resource/base.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);////비트맵 핸들얻어오는 과정 
	baseScreenHandle->dc = CreateCompatibleDC(hdc);//화면 에 호환되는 dc얻기 
	//hdc가 널이라 화면 에 호환되는 dc 가 자동으로m_base.dc에잭재된 ㅏㅇ태
	baseScreenHandle->hOldbmp = (HBITMAP)SelectObject(baseScreenHandle->dc, baseScreenHandle->hBmp);
	//dc랑 비트맵 핸들을 연결하고 이전상태를old 에 저장 . 
	GetObject(baseScreenHandle->hBmp, sizeof(BITMAP), &baseScreenHandle->bit);
	//핸들로 비트맵 구조체 필드를 채움.  너비랑 높이만 슬거임
	//m_Base.bit.bmWidth, bmHeight ..
	
	// init scene
	// 문제점 기록1 initScene을 클래스의 생성자에서 호출하면 HDC를 전달받지 못한 상태에서
	// 각 오브젝트들이 초기화되므로 dc가 올바르게 지정되지않아 화면에 오브젝트들이 출력되지않음
	initScene();
}
#pragma once
#include "scene.h"

class gameObject;
class bulletPool;
class enemyPool;

class galagaGameScene : public scene
{
public:
	galagaGameScene();
	~galagaGameScene();

	void initScene(HDC hdc);
	void initParam();
	void update();
	void draw();
	void input();

private:
	void togglePause();

	gameObject* backGround;
	gameObject* player;
	gameObject* boss01;
	gameObject* uiScoreObj;
	gameObject* uiPauseObj;
	// bullet을 처리할 오브젝트 풀
	bulletPool* bullets;
	// 잡몹 처리할 오브젝트 풀
	enemyPool* enemies;

	// gameScene의 스테이지 상태값
	int stageState;

	// 적 생성 딜레이
	int enemyGenerateCoolTime;

	// 게임 시작 딜레이
	int gameStartDelay;

	// 게임 퍼즈 플래그
	bool gamePauseFlag;

	int keyInputDelay;
	bool keyTrigger;
};
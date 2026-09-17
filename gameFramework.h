#pragma once

namespace sprites
{
	struct spriteHandle;
}

class gameObject;
class scene;

class gameFramework
{
public:
	gameFramework();
	~gameFramework();
	void gameLoop(HDC hdc);
	void drawScreen(HDC hdc);
	void update();

	void initScene();

	void initScreen(HDC hdc);

private:
	sprites::spriteHandle *baseScreenHandle;

	// current Scene pointer
	scene* currScene;
	scene* mainSceneObj;
	scene* gameSceneObj;
	
	// related update
	double msPerUpdate;
	double prevTick;
	double lag;
};
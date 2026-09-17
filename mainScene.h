#pragma once
#include "scene.h"

class gameObject;

class mainScene : public scene
{
public:
	mainScene();
	~mainScene();

	void initScene(HDC hdc);
	void initParam();
	void update();
	void draw();
	void input();

private:
	gameObject* backGround;
	gameObject* uiBtnSet;
};
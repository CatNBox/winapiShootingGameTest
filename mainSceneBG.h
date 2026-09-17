#pragma once
#include "gameObject.h"

class mainSceneBG : public gameObject
{
public:
	mainSceneBG(HDC rcvDC);
	~mainSceneBG();

	void draw();
	void update();

private:
};

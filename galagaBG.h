#pragma once
#include "gameObject.h"

class galagaBG : public gameObject
{
public:
	galagaBG(HDC rcvDC);
	~galagaBG();

	void draw();
	void update();

private:
};
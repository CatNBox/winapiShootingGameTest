#pragma once
#include <array>
#include "gameObject.h"

class uiNumber;

class uiScore : public gameObject
{
public:
	uiScore(HDC rcvDC);
	~uiScore();

	void update();
	void draw();

private:
	std::array<uiNumber*, 10> arrUINum;
	int prevScore;
};
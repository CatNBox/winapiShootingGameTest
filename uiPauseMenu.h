#pragma once
#include "gameObject.h"

namespace gameSysData
{
	enum class uiState;
}

class uiPauseMenu : gameObject
{
public:
	uiPauseMenu(HDC rcvDC);
	~uiPauseMenu();

	void initParam();
	void update();
	void draw();

	gameSysData::uiState getState();

private:
	gameObject* pauseBtn;
	gameSysData::uiState currState;
};
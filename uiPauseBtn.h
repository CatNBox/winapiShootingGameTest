#pragma once
#include "gameObject.h"

namespace gameSysData
{
	enum class uiState;
}

class uiPauseBtn : gameObject
{
public:
	uiPauseBtn(HDC rcvDC);
	~uiPauseBtn();

	void initParam();
	void update();
	void draw();

	gameSysData::uiState getState();

private:
	gameSysData::uiState currState;
};
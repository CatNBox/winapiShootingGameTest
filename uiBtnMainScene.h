#pragma once
#include "gameObject.h"

namespace gameSysData
{
	enum class uiState;
}

class uiBtnMainScene : public gameObject
{
public:
	uiBtnMainScene(HDC rcvDC);
	~uiBtnMainScene();

	void update();
	void draw();

	gameSysData::uiState getState();

private:
	gameSysData::uiState currState;
};
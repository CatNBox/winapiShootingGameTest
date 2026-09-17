#pragma once
#include <Windows.h>

namespace gameSysData
{
	enum class uiState;
}

class scene
{
public:
	scene();
	~scene();

	virtual void initScene(HDC hdc) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void input() = 0;

	gameSysData::uiState getUIState();

protected:
	gameSysData::uiState currUIState;

};
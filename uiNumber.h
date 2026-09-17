#pragma once
#include "gameObject.h"

class uiNumber : public gameObject
{
public:
	uiNumber(HDC rcvDC);
	~uiNumber();

	void init(int targetNum, long initX, long initY);
	void update();
	void draw();

	bool getVisible() const;
	void setVisible(bool rcvBool);

	void addPosX(int addValue);

private:
	bool isVisible;

	long sprOriX;
	long sprOriY;
	long sprWidth;
	long sprHeight;
};
#pragma once
#include <Windows.h>
#include <array>
#include "gameMetaData.h"

class bullet;

class bulletPool
{
public:
	bulletPool();
	~bulletPool();
	void releasePool();

	void initPool(HDC rcvDC);
	void update();
	void draw();
	bool create(galagaData::bulletType bulType, long initX, long initY, bool ally = false);

	bool chkConflict(long rcvX, long rcvY, long rcvWidth, long rcvHeight, bool ally = false);

private:
	void objSetDisable(bullet* rcvObj);

	std::array<bullet*, galagaData::maxBulletNum> pool;
	bullet* avaliableFirstObj;
};
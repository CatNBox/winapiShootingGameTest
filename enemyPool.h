#pragma once
#include <Windows.h>
#include <array>
#include "gameMetaData.h"

class bulletPool;
class galagaling;

class enemyPool
{
public:
	enemyPool();
	~enemyPool();
	void releasePool();

	void initPool(HDC rcvDC, bulletPool* bullets);
	void update();
	void draw();
	bool create(galagaData::galagaling::bodyType rcvType, long initX, long initY);

private:
	void objSetDisable(galagaling* rcvObj);

	std::array<galagaling*, galagaData::maxEnemyNum> pool;
	galagaling* avaliableFirstObj;
};
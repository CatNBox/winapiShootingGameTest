#include <algorithm>
#include "bulletPool.h"
#include "galagaling.h"
#include "enemyPool.h"

enemyPool::enemyPool()
{
}

enemyPool::~enemyPool()
{
	releasePool();
}

void enemyPool::releasePool()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		delete *itr;
	}
}

void enemyPool::initPool(HDC rcvDC, bulletPool* bullets)
{
	// 개체의 생성
	std::generate(pool.begin(), pool.end(),
		[rcvDC, bullets]() {
		return new galagaling(rcvDC, bullets);
	});

	// 사용가능한 개체 연결
	for (auto itr = pool.begin(); itr != pool.end() - 1; itr++)
	{
		(*itr)->setNext((*(itr + 1)));
	}

	// 사용가능한 링크드 리스트의 가장 첫번째 개체
	avaliableFirstObj = pool.at(0);
}

void enemyPool::update()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		galagaling* currObj = *itr;
		if (currObj->chkUsing() == true)
		{
			if (currObj->getState() == galagaData::galagaling::state::conflictEnd)
			{
				objSetDisable(currObj);
			}
			else if (currObj->chkScreenRangeOver() == false)
			{
				currObj->update();
			}
			else if (currObj->chkScreenRangeOver() == true)
			{
				objSetDisable(currObj);
			}
		}
	}
}

void enemyPool::draw()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		if ((*itr)->chkUsing() == true)
		{
			(*itr)->draw();
		}
	}
}

bool enemyPool::create(galagaData::galagaling::bodyType rcvType, long initX, long initY)
{
	if (avaliableFirstObj != nullptr)
	{
		auto currObj = avaliableFirstObj;
		avaliableFirstObj = currObj->getNext();
		currObj->init(rcvType, initX, initY);

		return true;
	}
	return false;
}

void enemyPool::objSetDisable(galagaling * rcvObj)
{
	rcvObj->initPosScreenOut();
	if (avaliableFirstObj == nullptr)
	{
	rcvObj->setNext(nullptr);
		avaliableFirstObj = rcvObj;
	}
	else if (avaliableFirstObj->chkUsing() == false)
	{
		rcvObj->setNext(avaliableFirstObj);
		avaliableFirstObj = rcvObj;
	}
}

#include <algorithm>
#include "bullet.h"
#include "bulletPool.h"

bulletPool::bulletPool()
{
}

bulletPool::~bulletPool()
{
	releasePool();
}

void bulletPool::releasePool()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		delete *itr;
	}
}

void bulletPool::initPool(HDC rcvDC)
{
	// 객체의 생성
	std::generate(pool.begin(),pool.end(),
		[rcvDC]() {
		return new bullet(rcvDC);
	});
	
	// 아직 활성화되지않은 객체들을 연결
	for (size_t i = 0; i < pool.size() - 1; i++)
	{
		pool[i]->info.next = pool[i + 1];
	}

	avaliableFirstObj = pool[0];
}

void bulletPool::update()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		bullet* currObj = *itr;
		if (currObj->chkUsing() == true)
		{
			if (currObj->getState() == galagaData::bulletState::conflict)
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

void bulletPool::draw()
{
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		if ((*itr)->chkUsing() == true)
		{
			(*itr)->draw();
		}
	}
}

bool bulletPool::create(galagaData::bulletType bulType, long initX, long initY, bool ally)
{
	if (avaliableFirstObj != nullptr)
	{
		auto currObj = avaliableFirstObj;
		avaliableFirstObj = currObj->getNext();
		currObj->init(bulType, initX, initY, ally);

		return true;
	}
	return false;
}

bool bulletPool::chkConflict(long rcvX, long rcvY, long rcvWidth, long rcvHeight, bool ally)
{
	// 순회하면서 히트박스와 충돌체크
	for (auto itr = pool.begin(); itr != pool.end(); itr++)
	{
		auto currObj = (*itr);
		if (currObj->chkAlly() == ally)
		{
			if (currObj->chkConflict(rcvX, rcvY, rcvWidth, rcvHeight) == true)
			{
				// 충돌했으므로 탄환상태를 충돌로 변경하고 true 반환
				currObj->changeState(galagaData::bulletState::conflict);

				return true;
			}
		}
	}
	return false;
}

void bulletPool::objSetDisable(bullet * rcvObj)
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

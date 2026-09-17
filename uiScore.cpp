#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
#include "uiNumber.h"
#include "uiScore.h"

uiScore::uiScore(HDC rcvDC)
	:gameObject(galagaResource::imgAddrScoreSprite, rcvDC)
{
	initPos(25, 25);

	std::generate(arrUINum.begin(),arrUINum.end(),
		[rcvDC]() {
		return new uiNumber(rcvDC);
	});

	prevScore = score;
}

uiScore::~uiScore()
{
}

void uiScore::update()
{
	// 가장 앞자리의 x위치 245
	// 자리수별로 숫자구하기
	if (prevScore < score)
	{
		auto currScore = score;
		for (int i = 0; i < 10; i++)
		{
			auto currNum = currScore % 10;
			arrUINum[i]->init(currNum, 245, 25);
			for (int j = i - 1; j >= 0; j--)
			{
				arrUINum[j]->addPosX(gameSysData::numSprData::width[currNum]);
			}

			currScore /= 10;
			if (currScore == 0)
			{
				break;
			}
		}
		prevScore = score;
	}
}

void uiScore::draw()
{
	gameObject::draw();
	for (auto itr = arrUINum.begin(); itr != arrUINum.end(); itr++)
	{
		auto currObj = *itr;
		if (currObj->getVisible() == true)
		{
			currObj->draw();
		}
		else
		{
			break;
		}
	}
}

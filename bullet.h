#pragma once
#include "gameObject.h"

namespace galagaData
{
	enum class bulletType;
	enum class bulletState;
}

class bullet : public gameObject
{
public:
	friend class bulletPool;
	~bullet();

	void init(galagaData::bulletType rcvBulType, long initX, long initY, bool ally = false);
	void update();
	void draw();

	void targetPos(long posX, long posY);

	bullet* getNext() const;
	void setNext(bullet* nextObj);

	bool chkScreenRangeOver();	// 화면을 벗어났는지 체크
	bool chkUsing();			// 현재 사용중인 개체인지 체크
	void setAvaliable();

	// 아군 총알인지 체크
	bool chkAlly();

	// 충돌 체크
	bool chkConflict(long rcvX, long rcvY, long rcvWidth, long rcvHeight);
	
	// 현재상태 변경
	void changeState(galagaData::bulletState rcvState);
	
	// 현재상태 반환
	galagaData::bulletState getState() const;

	// 위치를 화면밖으로 초기화
	void initPosScreenOut();

private:;
	bullet(HDC rcvDC);

	galagaData::bulletState currState;
	bool isAlly;
	bool isUsing;

	union {
		struct {
			long bulletSpeed;
			galagaData::bulletType bulType;
			// bullet move type

			// sprite data
			long sprOriX;
			long sprOriY;
			long sprWidth;
			long sprHeight;

			long targetPosX;
			long targetPosY;
		} activated;

		bullet* next;
	} info;
};
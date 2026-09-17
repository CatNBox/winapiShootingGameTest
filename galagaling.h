#pragma once
#include "gameObject.h"

namespace galagaData
{
	namespace galagaling
	{
		enum class bodyType;
	}
}
class bulletPool;

class galagaling : public gameObject
{
public:
	friend class enemyPool;
	~galagaling();

	void init(galagaData::galagaling::bodyType rcvType, long initX, long initY);

	void update();
	void draw();

	void targetPos(long posX, long posY);

	galagaling* getNext() const;
	void setNext(galagaling* nextObj);

	// 임시 체크
	bool chkScreenRangeOver();

	bool chkUsing();
	void setAvaliable();
	void changeState(galagaData::galagaling::state rcvState);
	galagaData::galagaling::state getState() const;

	// 위치를 화면 밖으로 초기화
	void initPosScreenOut();

	// 점수반영
	void applyScore();

	// idle 애니메이션
	void animaIdle();

	// 폭발 애니메이션
	void animaExplosion();

private:
	// 생성자 pool에서만 접근가능
	galagaling(HDC rcvDC, bulletPool* rcvPool);

	// 충돌판정
	void chkConflictBullet();

	bulletPool* bullets;
	galagaData::galagaling::state currState;
	bool isUsing;

	union {
		struct {
			galagaData::galagaling::bodyType galagaType;

			long moveSpeed;
			bool shootTrigger;
			int shootCoolDown;

			// sprite data
			long sprOriX;
			long sprOriY;
			long sprWidth;
			long sprHeight;
			int animeSpeed;

			/*long targetPosX;
			long targetPosY;*/

			// hitbox data
			long hitboxGapX;
			long hitboxGapY;
			long hitboxWidth;
			long hitboxHeight;
		} activated;

		galagaling* next;
	} info;
};
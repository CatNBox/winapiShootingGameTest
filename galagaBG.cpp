#include "sprites.h"
#include "galagaResourceAddr.h"
#include "galagaBG.h"

galagaBG::galagaBG(HDC rcvDC)
	:gameObject(galagaResource::imgAddrGalagaBG, rcvDC)
{
	// 위치 초기화
	initPos(0, 0);
}

galagaBG::~galagaBG()
{
}

void galagaBG::draw()
{
	BitBlt(baseDC,//데스티네이션 dc
		0,//어디서부터직을건지 x좌표
		0,
		sprHandles->bit.bmWidth,//직을 가로 길이
		sprHandles->bit.bmHeight,
		sprHandles->dc,//소스의 dc 
		0,//소스에서 어디서부터 직을건지 
		0,
		SRCCOPY); //고대로 직으라는 옵션 
}

void galagaBG::update()
{
}

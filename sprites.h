#pragma once
#include "framework.h"

namespace sprites
{
	//스프라이트 핸들 구조체
	struct spriteHandle
	{
		HBITMAP hBmp, hOldbmp;
		HDC dc;
		BITMAP bit;
		POINT pt;
	};
}
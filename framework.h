// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//추가헤더
#include <strsafe.h>
#include <Ole2.h>
#include <gdiplus.h>
#include "frameworkMetaData.h"
#pragma comment(lib,"gdiplus")

#pragma comment(lib,"Msimg32.lib")//주인공 투명값 포함해서 찍을라고추가 
#include "definesHeader.h"
#include "gameFramework.h"
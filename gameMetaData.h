#pragma once

#define metaLong static const long

namespace gameSysData
{
	metaLong baseGameTick = 16;

	metaLong resWidth = 1024;
	metaLong resHeight = 768;

	enum class stageState
	{
		stage1Normal = 0,
		stage1Hard = 1,
		stage1Last = 2
	};

	enum class uiState
	{
		idle = 0,
		onGameStart = 1,
		onExit = 2,
		gameStart = 3,
		exit = 4,
		return2Game = 5,
		return2Title = 6
	};

	namespace numSprData
	{
		metaLong oriX[10]
			= { 14,56,83,124,168,212,252,293,331,376 };
		metaLong oriY = 0;
		metaLong width[10]
			= { 38,23,37,40,41,45,39,35,40,38 };
		metaLong height = 40;
	}
}

namespace galagaData
{
	// È­¸é¿¡ Ç¥½ÃÇÒ °³Ã¼ ¼öÀÇ ÃÖ´ë°ª
	metaLong maxBulletNum = 1000;
	metaLong maxEnemyNum = 100;
	metaLong stage1GenerateCooltimeNormal = 800;
	metaLong stage1GenerateCooltimeHard = 480;
	metaLong stage1GenerateCooltimeLast = 160;

	namespace explosionData
	{
		metaLong oriX[8]
			= { 0,50,100,148,197,247,296,346 };
		metaLong oriY[8]
			= { 0,0,0,0,0,0,0,0 };
		metaLong width[8]
			= { 50,50,50,50,50,50,50,50 };
		metaLong height[8]
			= { 50,50,50,50,50,50,50,50 };
	}

	namespace fighterData
	{
		metaLong witdh = 54;
		metaLong height = 54;

		metaLong basicSpeed = 7;
		metaLong shootCoolDown = 80;
	}

	namespace bossData
	{
		metaLong width = 126;
		metaLong height = 126;
	}

	namespace galagaling
	{
		metaLong shootCoolDown = 1000;

		enum class state
		{
			normal = 0,
			conflict = 1,
			conflictEnd = 2
		};

		enum class bodyType
		{
			zakoUp = 0,
			goeiUp = 1,
			midoriUp = 2,

			zakoDown = 3,
			goeiDown = 4,
			midoriDown = 5
		};

		enum class score
		{
			zako = 20,
			goei = 40,
			midori = 100
		};

		//zakoUp, goeiUp, midoriUp, zakoDown, goeiDown, midoriDown
		metaLong moveSpeed[6]
			= { 0,0,0,3,5,10 };
		metaLong animeSpeed[6]
			= { 0,0,0,320,320,320 };

		metaLong oriX01[6]
			= { 0,0,0,1,225,1 };
		metaLong oriX02[6]
			= { 0,0,0,112,336,98 };

		metaLong oriY[6]
			= { 0,0,0,85,85,264 };
		metaLong width[6]
			= { 0,0,0,111,111,97 };
		metaLong height[6]
			= { 0,0,0,81,81,97 };

		metaLong hixboxGapX[6]
			= { 0,0,0,5,5,5 };
		metaLong hixboxGapY[6]
			= { 0,0,0,5,5,5 };
		metaLong hixboxWidth[6]
			= { 0,0,0,45,45,38 };
		metaLong hixboxHeight[6]
			= { 0,0,0,30,30,38 };

		//zako downside
		// x1 y85 width111 height81
		// x112 y85 width111 height81
		/*namespace zakoDown {
			metaLong animeSpeed = 160;

			metaLong oriX01 = 1;
			metaLong oriX02 = 112;

			metaLong oriY = 85;
			metaLong width = 111;
			metaLong height = 81;
		}*/
		
		
		//goei downside
		// x225 y85 width111 height81
		// x336 y85 width111 height81
		/*namespace goeiDown
		{
			metaLong animeSpeed = 320;

			metaLong oriX01 = 225;
			metaLong oriX02 = 336;

			metaLong oriY = 85;
			metaLong width = 111;
			metaLong height = 81;
		}*/

		//midori downside
		// x1 y226 width97 height97
		// x98 y226 width97 height97
		/*namespace midoriDown
		{
			metaLong animeSpeed = 112;

			metaLong oriX01 = 1;
			metaLong oriX02 = 98;

			metaLong oriY = 226;
			metaLong width = 97;
			metaLong height = 97;
		}*/

	}

	enum class bulletType
	{
		basicRedBullet = 1001,
		basicGreenBullet = 1002,
		basicYellowBullet = 1003,
		basicBlueBullet = 1004
	};

	enum class bulletState
	{
		normal = 0,
		conflict = 1
	};

	// ±âº»Åº
	namespace basicBullet
	{
		metaLong basicSpeed = 20;

		metaLong OriX = 12;
		metaLong Width = 8;
		metaLong Height = 12;

		// »¡°£Åº 12,11 8*12
		metaLong redOriY = 11;
		// ³ì»öÅº 12,29 8*12
		metaLong greenOriY = 29;
		// ³ë¶õÅº 12,47 8*12
		metaLong yellowOriY = 47;
		// ÆÄ¶õÅº 12,65 8*12
		metaLong blueOriY = 65;
	}
}
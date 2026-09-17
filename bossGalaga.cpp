#include "gameMetaData.h"
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "bossGalaga.h"

using namespace galagaData;

bossGalaga::bossGalaga(HDC rcvDC)
	:gameObject(galagaResource::imgAddrBossGalaga, rcvDC)
{
	initPosX(gameSysData::resWidth / 2 - bossData::width / 2);
	initPosY(150 - bossData::height / 2);
}

bossGalaga::~bossGalaga()
{
}

void bossGalaga::update()
{
}

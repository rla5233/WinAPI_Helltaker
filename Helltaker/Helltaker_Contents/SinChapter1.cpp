#include "SinChapter1.h"

#include "BackGround.h"

SinChapter1::SinChapter1()
{
}

SinChapter1::~SinChapter1()
{
}

void SinChapter1::BeginPlay()
{
	SinChapterManager::BeginPlay();
}

void SinChapter1::LevelStart(ULevel* _PrevLevel)
{
	SinChapterManager::LevelStart(_PrevLevel);

	M_CreateSinMap(1);

	M_StateChange(ESinState::Intro);
}

void SinChapter1::Phase1_Start()
{
	SinChapterManager::Phase1_Start();

	M_SetSmallChainVecSize(26, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(0, 0);
	M_CreateSmallVerChain_P1(1, 1);
	M_CreateSmallVerChain_P1(2, 2);
	M_CreateSmallVerChain_P1(3, 3);
	M_CreateSmallVerChain_P1(4, 4);
	M_CreateSmallVerChain_P1(6, 6);
	M_CreateSmallVerChain_P1(5, 7);
	M_CreateSmallVerChain_P1(4, 8);
	M_CreateSmallVerChain_P1(3, 9);
	M_CreateSmallVerChain_P1(2, 10);
	M_CreateSmallVerChain_P1(0, 12);
	M_CreateSmallVerChain_P1(2, 13);
	M_CreateSmallVerChain_P1(4, 14);
	M_CreateSmallVerChain_P1(1, 15);
	M_CreateSmallVerChain_P1(6, 15);
	M_CreateSmallVerChain_P1(0, 16);
	M_CreateSmallVerChain_P1(3, 16);
	M_CreateSmallVerChain_P1(2, 17);
	M_CreateSmallVerChain_P1(5, 17);
	M_CreateSmallVerChain_P1(4, 18);
	M_CreateSmallVerChain_P1(6, 19);
	M_CreateSmallVerChain_P1(3, 21);
	M_CreateSmallVerChain_P1(0, 22);
	M_CreateSmallVerChain_P1(6, 22);
	M_CreateSmallVerChain_P1(2, 23);
	M_CreateSmallVerChain_P1(4, 23);
	M_CreateSmallVerChain_P1(1, 24);
	M_CreateSmallVerChain_P1(5, 24);
	M_CreateSmallVerChain_P1(0, 25);
	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallVerChain_P1(6, 25);
}

void SinChapter1::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 1);
	M_CreateHitChain(ESinHitChainType::Right, 1);
	M_CreateHitChainHp("교만의 사슬");
}

void SinChapter1::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);
}

void SinChapter1::LevelEnd(ULevel* _NextLevel)
{
	SinChapterManager::LevelEnd(_NextLevel);
}
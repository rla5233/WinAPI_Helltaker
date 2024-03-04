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

	M_CreateSinMap();

	M_StateChange(ESinState::Intro);
}

void SinChapter1::Phase1Start()
{
	SinChapterManager::Phase1Start();

	M_SetSmallChainVecSize(26, 1);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 0, 0);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 1, 1);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 2, 2);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 3, 3);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 4, 4);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 6, 5);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 5, 6);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 4, 7);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 3, 8);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 2, 9);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 0, 10);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 2, 11);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 4, 12);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 1, 13);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 6, 13);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 0, 14);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 3, 14);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 2, 15);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 5, 15);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 4, 16);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 6, 17);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 3, 18);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 0, 19);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 6, 19);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 2, 20);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 4, 20);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 1, 21);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 5, 21);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 0, 22);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 3, 22);
	//M_CreateSmallChain(ESinSmallChainType::Ver, 1, 6, 22);
	
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 0, 0);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 1, 1);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 2, 2);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 3, 3);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 4, 4);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 0, 5);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 1, 6);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 2, 7);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 3, 8);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 4, 9);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 0, 10);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 1, 11);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 2, 12);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 3, 13);
	M_CreateSmallChain(ESinSmallChainType::Hor, 1, 4, 14);
}

void SinChapter1::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);
}

void SinChapter1::LevelEnd(ULevel* _NextLevel)
{
	SinChapterManager::LevelEnd(_NextLevel);
}
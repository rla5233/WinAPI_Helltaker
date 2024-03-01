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

	M_StateChange(ESinState::Phase1);
}

void SinChapter1::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);
}

void SinChapter1::LevelEnd(ULevel* _NextLevel)
{
	SinChapterManager::LevelEnd(_NextLevel);
}

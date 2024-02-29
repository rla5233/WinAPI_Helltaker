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

	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	SinBG->CreateBackGround("Sin_Pit");

	M_CreateSinBG("SinBG");
}

void SinChapter1::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);
}

void SinChapter1::LevelEnd(ULevel* _NextLevel)
{
	SinChapterManager::LevelEnd(_NextLevel);
}

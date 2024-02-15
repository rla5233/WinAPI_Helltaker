#include "Chapter1.h"

#include "ContentsHelper.h"

Chapter1::Chapter1()
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::BeginPlay()
{
	ChapterManager::BeginPlay();
	ContentsHelper::LoadImg("BackGround", "ChapterBG_001.png");
	ContentsHelper::LoadFolder("Chapter\\Demon", "PandeMonica");
}

void Chapter1::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, true , true , false },
		{ false, true , true , true , true , true , false },
		{ false, true , true , true , true , false, false },
		{ true , true , false, false, false, false, false },
		{ true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true  }
	};

	CreateChapterVec(Map);
	CreateHitActorVec();
	SetChapterStartLocation(6, 2);
	SetChapterEndPoint(5, 5);

	CreateBG("ChapterBG_001");
	CreateChapterUI();
	
	SpawnHero(5, 0);
	SpawnSkeleton(3, 1);
	SpawnSkeleton(2, 2);
	SpawnSkeleton(4, 2);
	SpawnStone(1, 4, "Stone_002.png");
	SpawnStone(1, 5, "Stone_004.png");
	SpawnStone(4, 4, "Stone_009.png");
	SpawnStone(3, 5, "Stone_005.png");
	SpawnDemon(6, 5, "PandeMonica");


	// 디버그용
	ShowLocationPoint();
}

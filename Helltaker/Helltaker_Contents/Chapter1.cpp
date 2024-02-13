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

	// 디버그 용
	ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
	ContentsHelper::LoadImg("Debuging", "RedPoint.png");
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
	SetChapterStartLocation({ 6, 2 });

	CreateBG("ChapterBG_001");
	CreateChapterUI();
	CreateHero(5, 0);
	CreateSkeleton(3, 1);
	CreateSkeleton(1, 1);
	CreateStone(1, 4, 2);
	CreateStone(1, 5, 4);


	// 디버그용
	ShowLocationPoint();
}

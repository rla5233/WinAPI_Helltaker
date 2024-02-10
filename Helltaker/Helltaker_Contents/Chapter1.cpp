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
	CreateMoveActorVec();
	SetChapterStartLocation({ 6, 2 });

	CreateBG("ChapterBG_001");
	CreateChapterUI();
	CreateHero(5, 0);
	CreateSkeleton(3, 1);
	CreateSkeleton(1, 1);


	// 디버그 용
	ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
	ContentsHelper::LoadImg("Debuging", "RedPoint.png");
	ShowLocationPoint();
}
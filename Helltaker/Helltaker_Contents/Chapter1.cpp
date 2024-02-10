#include "Chapter1.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Skeleton.h"
#include "Hero.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

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

	CreateChapterMap(Map);
	SetChapterStartLocation({ 6, 2 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* ChapterBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	ChapterBG->CreateBackGround("ChapterBG_001");
	CreateChapterUI();

	FVector TileScale = ContentsHelper::GetTileScale();
	Hero* NewHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	NewHero->SetActorLocation(ChapterPointToLocation(5, 0) + FVector(TileScale.X / 2.0f, TileScale.Y / 2.0f));
	NewHero->SetLocationPoint({ 5, 0 });

	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::Skeleton));
	NewSkeleton->SetActorLocation(ChapterPointToLocation(3, 1) + FVector(TileScale.X / 2.0f, TileScale.Y / 2.0f));
	NewSkeleton->SetLocationPoint({ 3, 1 });

	// 디버그 용
	ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
	ContentsHelper::LoadImg("Debuging", "RedPoint.png");
	ShowLocationPoint();
}
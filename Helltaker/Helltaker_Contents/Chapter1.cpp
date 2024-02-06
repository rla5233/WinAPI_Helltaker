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
	CreateChapterMap(7, 7);
	SetChapterStartLocation({ 7, 2 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* ChapterBG = SpawnActor<BackGround>();
	ChapterBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	ChapterBG->SetName("ChapterBG_001.png");
	ChapterBG->LoadBG();
	ChapterBG->SetBG();

	//UEngineDirectory ResourcesPath = UEngineDirectory();
	//ResourcesPath.MoveParent();
	//ResourcesPath.Move("Resources");

	Hero* NewHero = SpawnActor<Hero>();
	float hTileWidth = ContentsHelper::GetOneTileWidth() / 2;
	NewHero->SetActorLocation(ChapterPointToLocation(6, 0) + FVector(hTileWidth, hTileWidth));
	NewHero->SetLocationPoint({ 6, 0 });

	//Skeleton* NewSkeleton = SpawnActor<Skeleton>();
	//NewSkeleton->SetActorLocation(StagePointToLocation(2, 1));
	//NewSkeleton->SetLocationPoint({ 2, 1 });
}



#include "PlayStage1.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Skeleton.h"
#include "Hero.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

UPlayStage1::UPlayStage1()
{
}

UPlayStage1::~UPlayStage1()
{
}

void UPlayStage1::BeginPlay()
{
	StageManager::BeginPlay();

	// 스테이지 생성
	CreateStageMap(7, 7);
	SetStageStartLocation({ 7, 2 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* NewBG = SpawnActor<BackGround>();
	NewBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	NewBG->LoadRenderImage("Chapter", "ChapterBG_001.png");
	//NewBG->SetRenderImage("ChapterBG_001.png");


	//UEngineDirectory ResourcesPath = UEngineDirectory();
	//ResourcesPath.MoveParent();
	//ResourcesPath.Move("Resources");
	
	Hero* NewHero = SpawnActor<Hero>();
	float hTileWidth = ContentsHelper::GetOneTileWidth() / 2;
	NewHero->SetActorLocation(StagePointToLocation(6, 0) + FVector(hTileWidth, hTileWidth));
	NewHero->SetLocationPoint({ 6, 0 });
	
	//Skeleton* NewSkeleton = SpawnActor<Skeleton>();
	//NewSkeleton->SetActorLocation(StagePointToLocation(2, 1));
	//NewSkeleton->SetLocationPoint({ 2, 1 });
}

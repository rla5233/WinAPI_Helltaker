#include "PlayStage1.h"

#include "Helltaker_ContentsCore.h"
#include "BackGround.h"
#include "Hero.h"
#include "Skeleton.h"

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

	FVector WinScale = Helltaker_ContentsCore::GetWindowScale();
	BackGround* NewBG = SpawnActor<BackGround>();
	NewBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	NewBG->LoadAndSetRenderImage("StageBG_001.bmp");

	//UEngineDirectory ResourcesPath = UEngineDirectory();
	//ResourcesPath.MoveParent();
	//ResourcesPath.Move("Resources");
	
	Hero* NewHero = SpawnActor<Hero>();
	float hTileWidth = StageManager::GetOneTileWidth() / 2;
	NewHero->SetActorLocation(StagePointToLocation(6, 0) + FVector(hTileWidth, hTileWidth));
	NewHero->SetLocationPoint({ 6, 0 });
	
	//Skeleton* NewSkeleton = SpawnActor<Skeleton>();
	//NewSkeleton->SetActorLocation(StagePointToLocation(2, 1));
	//NewSkeleton->SetLocationPoint({ 2, 1 });
}

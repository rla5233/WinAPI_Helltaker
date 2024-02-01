#include "PlayStage1.h"

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
	SetStageStartLocation({ 7, 7 });

	BackGround* NewBG = SpawnActor<BackGround>();
	NewBG->SetActorLocation({ 1280 / 2, 720 / 2 });
	NewBG->LoadAndSetRenderImage("StageBG_001.bmp");

	//UEngineDirectory ResourcesPath = UEngineDirectory();
	//ResourcesPath.MoveParent();
	//ResourcesPath.Move("Resources");
	
	Hero* NewHero = SpawnActor<Hero>();
	NewHero->SetActorLocation(StagePointToLocation(6, 0));
	NewHero->SetLocationPoint({ 6, 0 });
	
	//Skeleton* NewSkeleton = SpawnActor<Skeleton>();
	//NewSkeleton->SetActorLocation(StagePointToLocation(2, 1));
	//NewSkeleton->SetLocationPoint({ 2, 1 });
}

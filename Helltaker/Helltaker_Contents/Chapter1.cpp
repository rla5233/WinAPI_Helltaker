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
	ChapterBG->CreateBackGround("ChapterBG_001");

	//Hero* NewHero = SpawnActor<Hero>();
	//float hTileWidth = ContentsHelper::GetOneTileWidth() / 2;
	//NewHero->SetActorLocation(ChapterPointToLocation(6, 0) + FVector(hTileWidth, hTileWidth));
	//NewHero->SetLocationPoint({ 6, 0 });
}



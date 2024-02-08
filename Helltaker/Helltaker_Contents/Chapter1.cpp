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
	CreateChapterMap(9, 7);
	SetChapterStartLocation({ 5, 2 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* ChapterBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	ChapterBG->CreateBackGround("ChapterBG_001");

	Hero* NewHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	FVector TileScale = ContentsHelper::GetTileScale();
	NewHero->SetActorLocation(ChapterPointToLocation(6, 0) + FVector(TileScale.X / 2.0f, TileScale.Y / 2.0f));
	NewHero->SetLocationPoint({ 6, 0 });


	// 디버그
	ContentsHelper::LoadImg("Debug", "GreenPoint.png");
	ShowLocationPoint();

	//RenderActor* GreenPoint = SpawnActor<RenderActor>(static_cast<int>(UpdateOrder::UI));
	//GreenPoint->SetActorLocation(GetChapterStartLocation());
	//GreenPoint->CreateImageRenderer(RenderOrder::UI);
	//GreenPoint->SetImg("GreenPoint.png");
	//GreenPoint->SetTransform({{ 0,0 }, {1, 1}});

}



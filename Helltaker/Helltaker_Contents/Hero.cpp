#include "Hero.h"

#include "ContentsHelper.h"

#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>


Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::BeginPlay()
{
	MoveActor::BeginPlay();

	SetName("Hero");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Left_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Right_Idle");

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Hero);
	Renderer->SetImage("Left_Idle");
	Renderer->SetTransform({ {0,0}, {TileWidth / 1.1f, TileWidth / 1.1f} });
	Renderer->CreateAnimation("Left_Idle", "Left_Idle", 0, 11, 0.07f, true);
	Renderer->ChangeAnimation("Left_Idle");
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}
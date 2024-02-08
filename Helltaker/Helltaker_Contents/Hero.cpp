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
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Left_Move");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Left_Kick");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Left_Victory");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Right_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Right_Move");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Right_Kick");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Right_Victory");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Death");

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Hero);
	// LEFT
	Renderer->SetImage("Left_Idle");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Left_Idle", "Left_Idle", 0, 11, 0.07f, true);

	Renderer->SetImage("Left_Move");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Left_Move", "Left_Move", 0, 5, 0.07f, true);

	Renderer->SetImage("Left_Kick");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Left_Kick", "Left_Kick", 0, 12, 0.07f, true);

	Renderer->SetImage("Left_Victory");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Left_Victory", "Left_Victory", 0, 16, 0.07f, true);

	// RIGHT
	Renderer->SetImage("Right_Idle");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Right_Idle", "Right_Idle", 0, 11, 0.07f, true);

	Renderer->SetImage("Right_Move");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Right_Move", "Right_Move", 0, 5, 0.07f, true);

	Renderer->SetImage("Right_Kick");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Right_Kick", "Right_Kick", 0, 12, 0.07f, true);

	Renderer->SetImage("Right_Victory");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Right_Victory", "Right_Victory", 0, 16, 0.07f, true);

	// DEATH
	Renderer->SetImage("Death");
	Renderer->SetTransform({ {0,0}, {TileScale.X / 1.1f, TileScale.Y / 1.1f} });
	Renderer->CreateAnimation("Death", "Death", 0, 17, 0.07f, true);


	// Init
	StateChange(EHeroState::Idle);
	SeeDirChange(EHeroSeeDir::Right);
	IdleStart();
}

void Hero::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EHeroState::Idle:
		Idle(_DeltaTime);
		break;
	case EHeroState::Move:
		Move(_DeltaTime);
		break;
	case EHeroState::Kick:
		Kick(_DeltaTime);
		break;
	case EHeroState::Victory:
		Victory(_DeltaTime);
		break;
	case EHeroState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Hero::Idle(float _DeltaTime)
{
	
}

void Hero::IdleStart()
{
	switch (SeeDir)
	{
	case EHeroSeeDir::Left:
		Renderer->ChangeAnimation("Left_Idle");
		break;
	case EHeroSeeDir::Right:
		Renderer->ChangeAnimation("Right_Idle");
		break;
	}
}

void Hero::Move(float _DeltaTime)
{
	Renderer->ChangeAnimation("Left_Move");
}

void Hero::MoveStart()
{
	switch (SeeDir)
	{
	case EHeroSeeDir::Left:
		Renderer->ChangeAnimation("Left_Move");
		break;
	case EHeroSeeDir::Right:
		Renderer->ChangeAnimation("Right_Move");
		break;
	}
}

void Hero::Kick(float _DeltaTime)
{
	Renderer->ChangeAnimation("Left_Kick");
}

void Hero::Victory(float _DeltaTime)
{
	Renderer->ChangeAnimation("Left_Victory");
}

void Hero::Death(float _DeltaTime)
{
	Renderer->ChangeAnimation("Death");
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Hero::StateChange(EHeroState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EHeroState::Idle:
			IdleStart();
			break;
		case EHeroState::Move:
			MoveStart();
			break;
		case EHeroState::Kick:
			//KickStart();
			break;
		case EHeroState::Victory:
			//MoveStart();
			break;
		case EHeroState::Death:
			//MoveStart();
			break;
		}
	}

	State = _State;
}

void Hero::SeeDirChange(EHeroSeeDir _Dir)
{
	SeeDir = _Dir;
}


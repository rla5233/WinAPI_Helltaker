#include "Hero.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

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
	SeeDirChange(EActorSeeDir::Right);
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

void Hero::ActionCheck(float _DeltaTime)
{
	
}

void Hero::Idle(float _DeltaTime)
{
	if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
	{
		ActionCheck(_DeltaTime);
		//MoveDirChange(EActorMoveDir::Up);
		//StateChange(EHeroState::Move);
	}
	else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
	{
		ActionCheck(_DeltaTime);
		//MoveDirChange(EActorMoveDir::Left);
		//SeeDirChange(EActorSeeDir::Left);
		//StateChange(EHeroState::Move);
	}
	else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
	{
		ActionCheck(_DeltaTime);
		//MoveDirChange(EActorMoveDir::Down);
		//StateChange(EHeroState::Move);
	}
	else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
	{
		ActionCheck(_DeltaTime);
		//MoveDirChange(EActorMoveDir::Right);
		//SeeDirChange(EActorSeeDir::Right);
		//StateChange(EHeroState::Move);
	}
}

void Hero::IdleStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Left_Idle");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Right_Idle");
		break;
	}
}

void Hero::Move(float _DeltaTime)
{
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		StateChange(EHeroState::Idle);
	}
}

void Hero::MoveStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Left_Move");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Right_Move");
		break;
	}

	FMoveDirCheck();
	MoveOn();
}

void Hero::Kick(float _DeltaTime)
{
}

void Hero::KickStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Left_Kick");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Right_Kick");
		break;
	}
}

void Hero::Victory(float _DeltaTime)
{
}

void Hero::VictoryStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Left_Victory");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Right_Victory");
		break;
	}
}

void Hero::Death(float _DeltaTime)
{
}

void Hero::DeathStart()
{}



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
			KickStart();
			break;
		case EHeroState::Victory:
			VictoryStart();
			break;
		case EHeroState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}
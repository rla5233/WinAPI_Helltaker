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
	SetTransform({ {0,0}, {TileScale.X * 0.9f, TileScale.Y * 0.9f} });
	
	SetImg("Left_Idle");
	CreateAnimation("Left_Idle", "Left_Idle", 0, 11, IdleInter, true);
	
	//SetImg("Left_Move");
	CreateAnimation("Left_Move", "Left_Move", 0, 5, MoveInter, false);
	
	//SetImg("Left_Kick");
	CreateAnimation("Left_Kick", "Left_Kick", 0, 12, KickInter, false);
	
	//SetImg("Left_Victory");
	CreateAnimation("Left_Victory", "Left_Victory", 0, 20, VictoryInter, false);
	
	//SetImg("Right_Idle");
	CreateAnimation("Right_Idle", "Right_Idle", 0, 11, IdleInter, true);
	
	//SetImg("Right_Move");
	CreateAnimation("Right_Move", "Right_Move", 0, 5, MoveInter, false);
	
	//SetImg("Right_Kick");
	CreateAnimation("Right_Kick", "Right_Kick", 0, 12, KickInter, false);
	
	//SetImg("Right_Victory");
	CreateAnimation("Right_Victory", "Right_Victory", 0, 20, VictoryInter, false);
	
	//SetImg("Death");
	CreateAnimation("Death", "Death", 0, 17, 0.07f, false);


	// Init
	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHeroState::Idle);
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
	const std::vector<std::vector<bool>>& Map = GetChapter()->GetChapterMap();
	FVector LocationPoint = GetLocationPoint();

	switch (MoveDir)
	{
	case EActorMoveDir::Left:
		LocationPoint += FVector::Left;
		SeeDirChange(EActorSeeDir::Left);
		break;
	case EActorMoveDir::Right:
		LocationPoint += FVector::Right;
		SeeDirChange(EActorSeeDir::Right);
		break;
	case EActorMoveDir::Up:
		LocationPoint += FVector::Up;
		break;
	case EActorMoveDir::Down:
		LocationPoint += FVector::Down;
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	if (0 <= LocationPoint.iY() && LocationPoint.iY() < Height
		&& 0 <= LocationPoint.iX() && LocationPoint.iX() < Width)
	{
		if (Map[LocationPoint.iY()][LocationPoint.iX()])
		{
			StateChange(EHeroState::Victory);
		}
		else
		{
			IdleStart();
		}
	}
	else
	{
		IdleStart();
	}
}

void Hero::Idle(float _DeltaTime)
{
	if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
	{
		MoveDirChange(EActorMoveDir::Up);
		ActionCheck(_DeltaTime);
	}
	else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
	{
		MoveDirChange(EActorMoveDir::Left);
		SeeDirChange(EActorSeeDir::Left);
		ActionCheck(_DeltaTime);
	}
	else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
	{
		MoveDirChange(EActorMoveDir::Down);
		ActionCheck(_DeltaTime);
	}
	else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
	{
		MoveDirChange(EActorMoveDir::Right);
		SeeDirChange(EActorSeeDir::Right);
		ActionCheck(_DeltaTime);
	}////////////
	else if (UEngineInput::IsPress('Q'))
	{
		StateChange(EHeroState::Kick);
	}
}

void Hero::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * IdleScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Left_Idle");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Right_Idle");
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
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * MoveScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Left_Move");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Right_Move");
		break;
	}

	FMoveDirCheck();
	MoveOn();
}

void Hero::Kick(float _DeltaTime)
{
	if (0 > KickTimeCount)
	{
		StateChange(EHeroState::Idle);
		KickTimeCount = KickTime;
		return;
	}

	KickTimeCount -= _DeltaTime;
}

void Hero::KickStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * KickScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Left_Kick");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Right_Kick");
		break;
	}
}

void Hero::Victory(float _DeltaTime)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	float Diff_Y = TileScale.Y * (IdleScale.Y - VictoryScale.Y) / 2.0f;
	SetTransform({ {0.0f, Diff_Y}, {TileScale * VictoryScale} });

	if (0 > VictoryTimeCount)
	{
		VictoryTimeCount = VictoryTime;
		return;
	}

	VictoryTimeCount -= _DeltaTime;
}

void Hero::VictoryStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Left_Victory");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Right_Victory");
		break;
	}
}

void Hero::Death(float _DeltaTime)
{
}

void Hero::DeathStart()
{

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
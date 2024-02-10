#include "Hero.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"
#include "Skeleton.h"

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
	SetMoveActorType(EMoveActorType::Hero);
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Left_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Left_Move");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Left_Kick");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Left_Victory");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Right_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Right_Move");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Right_Kick");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Right_Victory");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Hero", "Hero_Death");

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Hero);
	SetTransform({ {0,0}, {TileScale * IdleScale} });
	
	SetImg("Hero_Left_Idle");
	CreateAnimation("Hero_LIdle", "Hero_Left_Idle", 0, 11, IdleInter, true);
	
	//SetImg("Left_Move");
	CreateAnimation("Hero_LMove", "Hero_Left_Move", 0, 5, MoveInter, false);
	
	//SetImg("Left_Kick");
	CreateAnimation("Hero_LKick", "Hero_Left_Kick", 0, 12, KickInter, false);
	
	//SetImg("Left_Victory");
	CreateAnimation("Hero_LVictory", "Hero_Left_Victory", 0, 20, VictoryInter, false);
	
	//SetImg("Right_Idle");
	CreateAnimation("Hero_RIdle", "Hero_Right_Idle", 0, 11, IdleInter, true);
	
	//SetImg("Right_Move");
	CreateAnimation("Hero_RMove", "Hero_Right_Move", 0, 5, MoveInter, false);
	
	//SetImg("Right_Kick");
	CreateAnimation("Hero_RKick", "Hero_Right_Kick", 0, 12, KickInter, false);
	
	//SetImg("Right_Victory");
	CreateAnimation("Hero_RVictory", "Hero_Right_Victory", 0, 20, VictoryInter, false);
	
	//SetImg("Death");
	CreateAnimation("Hero_Death", "Hero_Death", 0, 17, 0.07f, false);


	// Init
	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHeroState::Idle);
}

void Hero::ActionCheck()
{
	const std::vector<std::vector<bool>>& Map = GetChapter()->GetChapterVec();
	FVector CurLocationPoint = GetLocationPoint();

	switch (MoveDir)
	{
	case EActorMoveDir::Left:
		SetNextLocationPoint(CurLocationPoint + FVector::Left);
		SeeDirChange(EActorSeeDir::Left);
		break;
	case EActorMoveDir::Right:
		SetNextLocationPoint(CurLocationPoint + FVector::Right);
		SeeDirChange(EActorSeeDir::Right);
		break;
	case EActorMoveDir::Up:
		SetNextLocationPoint(CurLocationPoint + FVector::Up);
		break;
	case EActorMoveDir::Down:
		SetNextLocationPoint(CurLocationPoint + FVector::Down);
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	int Next_X = GetNextLocationPoint().iX();
	int Next_Y = GetNextLocationPoint().iY();
	if (0 <= Next_Y && Next_Y < Height && 0 <= Next_X && Next_X < Width)
	{
		if (Map[Next_Y][Next_X])
		{
			NextTileCheck(Next_X, Next_Y);			
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

void Hero::NextTileCheck(int _X, int _Y)
{
	if (nullptr == GetChapter()->GetMoveActor(_X, _Y))
	{
		StateChange(EHeroState::Move);
	}
	else
	{
		StateChange(EHeroState::Kick);
	}
}

void Hero::Idle(float _DeltaTime)
{
	if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
	{
		MoveDirChange(EActorMoveDir::Up);
		ActionCheck();
	}
	else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
	{
		MoveDirChange(EActorMoveDir::Left);
		SeeDirChange(EActorSeeDir::Left);
		ActionCheck();
	}
	else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
	{
		MoveDirChange(EActorMoveDir::Down);
		ActionCheck();
	}
	else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
	{
		MoveDirChange(EActorMoveDir::Right);
		SeeDirChange(EActorSeeDir::Right);
		ActionCheck();
	}
}

void Hero::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * IdleScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Hero_LIdle");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Hero_RIdle");
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
		ChangeAnimation("Hero_LMove");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Hero_RMove");
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

	FVector NextLocationPoint = GetNextLocationPoint();
	MoveActor* Other = GetChapter()->GetMoveActor(NextLocationPoint.iX(), NextLocationPoint.iY());
	

	switch (Other->GetMoveActorType())
	{
	case EMoveActorType::Skeleton:
	{
		Skeleton* OtherSkeleton = dynamic_cast<Skeleton*>(Other);
		OtherSkeleton->StateChange(ESkeletonState::Hit, MoveDir);
		break;
	}
	case EMoveActorType::Stone:
	{
		// Ãß°¡
		break;
	}
	}
	

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Hero_LKick");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Hero_RKick");
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
		ChangeAnimation("Hero_LVictory");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Hero_RVictory");
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
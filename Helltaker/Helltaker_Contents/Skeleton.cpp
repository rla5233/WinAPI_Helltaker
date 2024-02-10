#include "Skeleton.h"

#include "ChapterManager.h"

#include <EngineCore/EngineCore.h>

Skeleton::Skeleton()
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	MoveActor::BeginPlay();

	SetName("Skeleton"); 
	SetMoveActorType(EMoveActorType::Skeleton);
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Left_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Right_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Left_Hit");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Right_Hit");

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Skeleton);
	SetTransform({ {0,0}, {TileScale * IdleScale} });

	SetImg("Skeleton_Left_Idle");
	CreateAnimation("Skeleton_LIdle", "Skeleton_Left_Idle", 0, 11, IdleInter, true);
	CreateAnimation("Skeleton_RIdle", "Skeleton_Right_Idle", 0, 11, IdleInter, true);
	CreateAnimation("Skeleton_LHit", "Skeleton_Left_Hit", 0, 5, HitInter, false);
	CreateAnimation("Skeleton_RHit", "Skeleton_Right_Hit", 0, 5, HitInter, false);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(ESkeletonState::Idle);
}


void Skeleton::DeathCheck()
{
	const std::vector<std::vector<bool>>& Map = GetChapter()->GetChapterVec();
	FVector CurLocationPoint = GetLocationPoint();

	switch (MoveDir)
	{
	case EActorMoveDir::Left:
		SetNextLocationPoint(CurLocationPoint + FVector::Left);
		break;
	case EActorMoveDir::Right:
		SetNextLocationPoint(CurLocationPoint + FVector::Right);
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
			FMoveDirCheck();
			MoveOn();
			//NextTileCheck(Next_X, Next_Y);
		}
		else
		{
			StateChange(ESkeletonState::Idle);
		}
	}
	else
	{
		StateChange(ESkeletonState::Idle);
	}
}

void Skeleton::NextTileCheck(int _X, int _Y)
{
}

void Skeleton::Idle(float _DeltaTime)
{
}

void Skeleton::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * IdleScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Skeleton_LIdle");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Skeleton_RIdle");
		break;
	}
}

void Skeleton::Hit(float _DeltaTime)
{
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		StateChange(ESkeletonState::Idle);
	}
}

void Skeleton::HitStart(EActorMoveDir _OtherMoveDir)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * HitScale} });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ChangeAnimation("Skeleton_LHit");
		break;
	case EActorSeeDir::Right:
		ChangeAnimation("Skeleton_RHit");
		break;
	}

	switch (_OtherMoveDir)
	{
	case EActorMoveDir::Left:
		SeeDirChange(EActorSeeDir::Right);
		MoveDirChange(EActorMoveDir::Left);
		break;
	case EActorMoveDir::Right:
		SeeDirChange(EActorSeeDir::Left);
		MoveDirChange(EActorMoveDir::Right);
		break;
	case EActorMoveDir::Up:
		MoveDirChange(EActorMoveDir::Up);
		break;
	case EActorMoveDir::Down:
		MoveDirChange(EActorMoveDir::Down);
		break;
	}

	DeathCheck();	
}

void Skeleton::Death(float _DeltaTime)
{
}

void Skeleton::DeathStart()
{
}


void Skeleton::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Skeleton::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESkeletonState::Idle:
		Idle(_DeltaTime);
		break;
	case ESkeletonState::Hit:
		Hit(_DeltaTime);
		break;
	case ESkeletonState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Skeleton::StateChange(ESkeletonState _State, EActorMoveDir _OtherMoveDir)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESkeletonState::Idle:
			IdleStart();
			break;
		case ESkeletonState::Hit:
			HitStart(_OtherMoveDir);
			break;
		case ESkeletonState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}
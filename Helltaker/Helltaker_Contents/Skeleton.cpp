#include "Skeleton.h"

#include <EngineCore/EngineCore.h>



Skeleton::Skeleton()
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	MoveActor::BeginPlay();

	SetName("Skeleton");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Left_Idle");
	ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Right_Idle");

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Skeleton);
	SetTransform({ {0,0}, {TileScale * IdleScale} });

	SetImg("Skeleton_Left_Idle");
	CreateAnimation("Skeleton_LIdle", "Skeleton_Left_Idle", 0, 11, IdleInter, true);
	CreateAnimation("Skeleton_RIdle", "Skeleton_Right_Idle", 0, 11, IdleInter, true);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(ESkeletonState::Idle);
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
}

void Skeleton::HitStart()
{
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

void Skeleton::StateChange(ESkeletonState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESkeletonState::Idle:
			IdleStart();
			break;
		case ESkeletonState::Hit:
			HitStart();
			break;
		case ESkeletonState::Death:
			DeathStart();
			break;
		}
	}
	     
	State = _State;
}

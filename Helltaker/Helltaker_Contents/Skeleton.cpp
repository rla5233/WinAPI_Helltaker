#include "Skeleton.h"

#include "ChapterManager.h"

#include <EngineCore/EngineCore.h>

bool Skeleton::IsLoad = false;

Skeleton::Skeleton()
	: HitActor(ContentsHelper::GetWindowScale().X * (0.6f), ContentsHelper::GetWindowScale().X* (-1.5f))
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	HitActor::BeginPlay();

	SetName("Skeleton"); 
	SetMoveActorType(EMoveActorType::Skeleton);
	
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Left_Idle");
		ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Right_Idle");
		ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Left_Hit");
		ContentsHelper::LoadFolder("Characters\\Chapter\\Skeleton", "Skeleton_Right_Hit");
		
		IsLoad = true;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	CreateImageRenderer(RenderOrder::Skeleton);
	SetTransform({ {0,0}, {TileScale * IdleScale} });

	SetImg("Skeleton_Left_Idle");
	CreateAnimation("Skeleton_LIdle", "Skeleton_Left_Idle", 0, 11, IdleInter, true);
	CreateAnimation("Skeleton_RIdle", "Skeleton_Right_Idle", 0, 11, IdleInter, true);
	CreateAnimation("Skeleton_LHit", "Skeleton_Left_Hit", 0, 8, HitInter, false);
	CreateAnimation("Skeleton_RHit", "Skeleton_Right_Hit", 0, 8, HitInter, false);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHitActorState::Idle);
}


void Skeleton::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	HitActor::NextStateCheck(_OtherMoveDir);

	const std::vector<std::vector<bool>>& Map = GetChapter()->GetChapterVec();
	FVector CurLocationPoint = GetLocationPoint();

	switch (_OtherMoveDir)
	{
	case EMoveActorDir::Left:
		SeeDirChange(EActorSeeDir::Right);
		MoveDirChange(EMoveActorDir::Left);
		break;
	case EMoveActorDir::Right:
		SeeDirChange(EActorSeeDir::Left);
		MoveDirChange(EMoveActorDir::Right);
		break;
	case EMoveActorDir::Up:
		MoveDirChange(EMoveActorDir::Up);
		break;
	case EMoveActorDir::Down:
		MoveDirChange(EMoveActorDir::Down);
		break;
	}

	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		SetNextLocationPoint(CurLocationPoint + FVector::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurLocationPoint + FVector::Right);
		break;
	case EMoveActorDir::Up:
		SetNextLocationPoint(CurLocationPoint + FVector::Up);
		break;
	case EMoveActorDir::Down:
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
			return;
		}
	}

	StateChange(EHitActorState::Death);
}

void Skeleton::NextTileCheck(int _X, int _Y)
{
	HitActor::NextTileCheck(_X, _Y);

	if (nullptr == GetChapter()->GetHitActor(_X, _Y))
	{
		StateChange(EHitActorState::Hit);
	}
	else
	{
		StateChange(EHitActorState::Death);
	}	
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
	if (true == IsMove())
	{
		MoveOneBlock(_DeltaTime);
	}

	if (false == IsMove())
	{
		StateChange(EHitActorState::HitMoveEnd);
	}

	if (0 > HitTimeCount)
	{
		StateChange(EHitActorState::Idle);
		HitTimeCount = HitTime;
		return;
	}
	
	HitTimeCount -= _DeltaTime;
}

void Skeleton::HitMoveEnd(float _DeltaTime)
{
	if (0 > HitTimeCount)
	{
		StateChange(EHitActorState::Idle);
		HitTimeCount = HitTime;
		return;
	}

	HitTimeCount -= _DeltaTime;
}

void Skeleton::HitStart(EMoveActorDir _OtherMoveDir)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0, 0}, {TileScale * HitScale} });
	HitTimeCount = HitTime;

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		AnimationReset();
		ChangeAnimation("Skeleton_LHit");
		break;
	case EActorSeeDir::Right:
		AnimationReset();
		ChangeAnimation("Skeleton_RHit");
		break;
	}

	MoveOn();
	HitActorVecUpdate(EHitActorState::Hit);
}

void Skeleton::Death(float _DeltaTime)
{
	Destroy(0.0f);
}

void Skeleton::DeathStart()
{
	HitActorVecUpdate(EHitActorState::Death);
	CallDestroy();
}

void Skeleton::Tick(float _DeltaTime)
{
	HitActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Skeleton::StateUpdate(float _DeltaTime)
{
	HitActor::StateUpdate(_DeltaTime);

	switch (GetHitActorState())
	{
	case EHitActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EHitActorState::Hit:
		Hit(_DeltaTime);
		break;
	case EHitActorState::HitMoveEnd:
		HitMoveEnd(_DeltaTime);
		break;
	case EHitActorState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Skeleton::StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir)
{
	HitActor::StateChange(_State, _OtherMoveDir);

	if (GetHitActorState() != _State)
	{
		switch (_State)
		{
		case EHitActorState::Idle:
			IdleStart();
			break;
		case EHitActorState::Hit:
			HitStart(_OtherMoveDir);
			break;
		case EHitActorState::Death:
			DeathStart();
			break;
		}
	}

	SetHitActorState(_State);
}
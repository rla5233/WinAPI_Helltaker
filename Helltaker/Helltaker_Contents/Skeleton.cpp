#include "Skeleton.h"

#include "ChapterManager.h"

bool Skeleton::IsLoad = false;

Skeleton::Skeleton()
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	HitActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Left_Idle");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Right_Idle");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Left_Hit");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Right_Hit");
		
		IsLoad = true;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer = CreateImageRenderer(RenderOrder::HitActor);
	ImageRenderer->SetTransform({ {0,0}, {TileScale * IdleScale} });

	ImageRenderer->SetImage("Skeleton_Left_Idle");
	ImageRenderer->CreateAnimation("Skeleton_LIdle", "Skeleton_Left_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Skeleton_RIdle", "Skeleton_Right_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Skeleton_LHit", "Skeleton_Left_Hit", 0, 8, HitInter, false);
	ImageRenderer->CreateAnimation("Skeleton_RHit", "Skeleton_Right_Hit", 0, 8, HitInter, false);

	CreateBigHitEffect();

	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHitActorState::Idle);
}

// 수정 (Stone, HitActor virtual 관계 리팩토링 가능?)
void Skeleton::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	HitActor::NextStateCheck(_OtherMoveDir);

	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
	Point CurPoint = GetLocationPoint();

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
		SetNextLocationPoint(CurPoint + Point::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurPoint + Point::Right);
		break;
	case EMoveActorDir::Up:
		SetNextLocationPoint(CurPoint + Point::Up);
		break;
	case EMoveActorDir::Down:
		SetNextLocationPoint(CurPoint + Point::Down);
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	Point NextPoint = GetNextLocationPoint();
	if (0 <= NextPoint.Y && NextPoint.Y < Height && 0 <= NextPoint.X && NextPoint.X < Width)
	{
		if (true == Map[NextPoint.Y][NextPoint.X].IsVaild)
		{
			NextTileCheck(NextPoint);
			return;
		}
	}

	StateChange(EHitActorState::Death);
}

void Skeleton::NextTileCheck(Point _Point)
{
	if (nullptr == GetChapter()->M_GetHitActor(_Point))
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
	EffectEndCheck();
	Point CurPoint = GetLocationPoint();
	if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
	{
		StateChange(EHitActorState::Death);
	}
}

void Skeleton::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * IdleScale }});

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Skeleton_LIdle");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Skeleton_RIdle");
		break;
	}
}

void Skeleton::Hit(float _DeltaTime)
{
	StateChange(EHitActorState::Move);
}

void Skeleton::Move(float _DeltaTime)
{
	EffectEndCheck();
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		Point CurPoint = GetLocationPoint();
		if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
		{
			StateChange(EHitActorState::Death);
			return;
		}

		if (true == ImageRenderer->IsCurAnimationEnd())
		{
			StateChange(EHitActorState::Idle);
		}
	}
}

void Skeleton::MoveStart()
{
	MoveActor::MoveStart();

	HitActorInfoUpdate(EHitActorState::Move);
}

void Skeleton::HitStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * HitScale } });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Skeleton_LHit");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Skeleton_RHit");
		break;
	}

	SetRandomBigHitEffect();
}

void Skeleton::Death(float _DeltaTime)
{
	if (true == HitEffectEndCheck())
	{
		Destroy();	
	}
}

void Skeleton::DeathStart()
{
	SetRandomBigHitEffect();
	ImageRenderer->ActiveOff();

	HitActorInfoUpdate(EHitActorState::Death);
	InformDestroytoChapter();
}

void Skeleton::Tick(float _DeltaTime)
{
	HitActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Skeleton::StateUpdate(float _DeltaTime)
{
	switch (GetHitActorState())
	{
	case EHitActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EHitActorState::Hit:
		Hit(_DeltaTime);
		break;
	case EHitActorState::Move:
		Move(_DeltaTime);
		break;
	case EHitActorState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Skeleton::StateChange(EHitActorState _State)
{
	if (GetHitActorState() != _State)
	{
		switch (_State)
		{
		case EHitActorState::Idle:
			IdleStart();
			break;
		case EHitActorState::Hit:
			HitStart();
			break;
		case EHitActorState::Move:
			MoveStart();
			break;
		case EHitActorState::Death:
			DeathStart();
			break;
		}
	}

	SetHitActorState(_State);
}
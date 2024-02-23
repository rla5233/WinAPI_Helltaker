#include "Stone.h"

#include "ChapterManager.h"

bool Stone::IsLoad = false;

Stone::Stone()
{
}

Stone::~Stone()
{
}

void Stone::BeginPlay()
{
	HitActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_002.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_003.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_004.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_005.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_006.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_007.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_008.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_009.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_010.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_011.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Stone", "Stone_012.png");

		IsLoad = true;
	}

	Renderer = CreateImageRenderer(RenderOrder::HitActor);
	CreateSmallHitEffect();

	StateChange(EHitActorState::Idle);
}

void Stone::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	Point CurPoint = GetLocationPoint();

	switch (_OtherMoveDir)
	{
	case EMoveActorDir::Left:
		MoveDirChange(EMoveActorDir::Left);
		break;
	case EMoveActorDir::Right:
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

	StateChange(EHitActorState::Hit);
}

void Stone::NextTileCheck(Point _Point)
{
	HitActor::NextTileCheck(_Point);

	if (nullptr == GetChapter()->M_GetHitActor(_Point))
	{
		StateChange(EHitActorState::Move);
	}
	else
	{
		StateChange(EHitActorState::Idle);
	}
}

void Stone::IdleStart()
{
}

void Stone::Idle(float _DeltaTime)
{
	HitEffectEndCheck();
}

void Stone::HitStart(EMoveActorDir _OtherMoveDir)
{
	SetRandomSmallHitEffect();
}

void Stone::Hit(float _DeltaTime)
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
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

	StateChange(EHitActorState::Idle);
}

void Stone::Move(float _DeltaTime)
{
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		StateChange(EHitActorState::Idle);
	}
}

void Stone::MoveStart()
{
	MoveActor::MoveStart();

	HitActorInfoUpdate(EHitActorState::Move);
}

void Stone::SetStoneImg(std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Renderer->SetImage(_Name);
	Renderer->SetTransform({ {0.0f, TileScale.Y * (-0.125f)}, {TileScale * StoneScale} });
}

void Stone::Tick(float _DeltaTime)
{
	HitActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Stone::StateUpdate(float _DeltaTime)
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
	case EHitActorState::Move:
		Move(_DeltaTime);
		break;
	}
}

void Stone::StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir)
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
		case EHitActorState::Move:
			MoveStart();
			break;
		}
	}

	SetHitActorState(_State);
}
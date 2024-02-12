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

	SetName("Stone");

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_001.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_002.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_003.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_004.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_005.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_006.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_007.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_008.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_009.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_010.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_011.png");
		ContentsHelper::LoadImg("Characters\\Chapter\\Stone", "Stone_012.png");

		IsLoad = true;
	}

	CreateImageRenderer(RenderOrder::Stone);

	StateChange(EHitActorState::Idle);
}

void Stone::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	const std::vector<std::vector<bool>>& Map = GetChapter()->GetChapterVec();
	FVector CurLocationPoint = GetLocationPoint();

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

	StateChange(EHitActorState::Idle);
}

void Stone::NextTileCheck(int _X, int _Y)
{
	HitActor::NextTileCheck(_X, _Y);

	if (nullptr == GetChapter()->GetHitActor(_X, _Y))
	{
		StateChange(EHitActorState::Hit);
	}
	else
	{
		// Block : ½ºÅæ Áøµ¿
		StateChange(EHitActorState::Idle);
	}
}

void Stone::IdleStart()
{
}

void Stone::Idle(float _DeltaTime)
{
}

void Stone::HitStart(EMoveActorDir _OtherMoveDir)
{
}

void Stone::Hit(float _DeltaTime)
{
}

void Stone::HitMoveEnd(float _DeltaTime)
{
}

void Stone::SetStoneType(int _Type)
{
	switch (_Type)
	{
	case 1:
		SetImg("Stone_001.png");
		break;
	case 2:
		SetImg("Stone_002.png");
		break;
	case 3:
		SetImg("Stone_003.png");
		break;
	case 4:
		SetImg("Stone_004.png");
		break;
	case 5:
		SetImg("Stone_005.png");
		break;
	case 6:
		SetImg("Stone_006.png");
		break;
	case 7:
		SetImg("Stone_007.png");
		break;
	case 8:
		SetImg("Stone_008.png");
		break;
	case 9:
		SetImg("Stone_009.png");
		break;
	case 10:
		SetImg("Stone_010.png");
		break;
	case 11:
		SetImg("Stone_011.png");
		break;
	case 12:
		SetImg("Stone_012.png");
		break;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ {0,0}, {TileScale * StoneScale} });
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
	case EHitActorState::HitMoveEnd:
		HitMoveEnd(_DeltaTime);
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
		}
	}

	SetHitActorState(_State);
}
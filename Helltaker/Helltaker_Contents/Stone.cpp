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

	Renderer = CreateImageRenderer(RenderOrder::Stone);

	StateChange(EHitActorState::Idle);
}

void Stone::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetChapterInfoVec();
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
		if (true == Map[Next_Y][Next_X].IsVaild)
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
	MoveOn();
	HitActorInfoUpdate(EHitActorState::Hit);
}

void Stone::Hit(float _DeltaTime)
{
	if (true == IsMove())
	{
		MoveOneBlock(_DeltaTime);
	}

	if (false == IsMove())
	{
		StateChange(EHitActorState::Idle);
	}
}

void Stone::HitMoveEnd(float _DeltaTime)
{

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
#include "Hero.h"

#include "ChapterManager.h"

#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineSound.h>

Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::ActionCheck()
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
	Point CurPoint = GetLocationPoint();
	
	switch (GetMoveDir())
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
			if (0 >= ActionPoint)
			{
				StateChange(EHeroState::Death);
				return;
			}

			NextTileCheck(NextPoint);
			return;
		}
	}
	
	StateChange(EHeroState::None);
	StateChange(EHeroState::Idle);
}

void Hero::NextTileCheck(Point _Point)
{
	if (true == GetChapter()->IsLockBoxPoint() && IsHaveKey)
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Move);
		GetChapter()->DeleteLockBox();
		return;
	}

	if (nullptr == GetChapter()->M_GetHitActor(_Point))
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Move);

		if (true == GetChapter()->IsKeyPoint())
		{
			GetChapter()->DeleteKey();
			IsHaveKey = true;
		}
	}
	else
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Kick);
	}
}

void Hero::ThornHitCheck()
{
	HitActor::ThornHitCheck();

	// Cheat
	if (true == IsCheatOn())
	{
		return;
	}

	Point CurPoint = GetLocationPoint();
	if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
	{
		CreateRandomHitEffect();
		
		int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
		switch (RandomValue)
		{
		case 1:
			UEngineSound::SoundPlay("player_damage_001.wav");
			break;
		case 2:
			UEngineSound::SoundPlay("player_damage_002.wav");
			break;
		}
		
		--ActionPoint;
	}
}

void Hero::KickCheck()
{
	ThornHitCheck();
	UpdateActionPoint();
	GetChapter()->M_UpdateHeroActionPoint();
}

void Hero::MoveStart()
{
	HeroBase::MoveStart();
	CreateRandomMoveEffect();

	GetChapter()->M_ChangeThornState();
	UpdateActionPoint();
}

void Hero::Move(float _DeltaTime)
{
	FVector CurLocation = GetActorLocation();

	HeroBase::Move(_DeltaTime);

	FVector NextLocation = GetActorLocation();
	FVector Diff = NextLocation - CurLocation;
	if (GetPMoveDir() == Point::Down || GetPMoveDir() == Point::Up)
	{
		GetChapter()->CameraPosUpdate(Diff);
	}

	if (false == IsMove())
	{
		GetChapter()->M_UpdateHeroActionPoint();
	}
}

void Hero::KickStart()
{
	HeroBase::KickStart();

	GetChapter()->M_ChangeThornState();

	Point NextPoint = GetNextLocationPoint();
	HitActor* Other = GetChapter()->M_GetHitActor(NextPoint);
	Other->NextStateCheck(GetMoveDir());
}

void Hero::DeathStart()
{
	HeroBase::DeathStart();

	GetChapter()->M_StateChange(EChapterState::HeroDeath);
}

void Hero::UpdateActionPoint()
{
	// Cheat
	if (true == IsCheatOn())
	{
		return;
	}

	--ActionPoint;
}
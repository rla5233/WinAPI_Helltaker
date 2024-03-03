#include "Hero.h"

#include "ChapterManager.h"
#include "ContentsHelper.h"
#include "Skeleton.h"

#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::ActionCheck()
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
	Point CurPoint = GetLocationPoint();
	
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		SetNextLocationPoint(CurPoint + Point::Left);
		SeeDirChange(EActorSeeDir::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurPoint + Point::Right);
		SeeDirChange(EActorSeeDir::Right);
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
	if (true == GetCheatMode())
	{
		return;
	}

	Point CurPoint = GetLocationPoint();
	if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
	{
		CreateRandomHitEffect();
		--ActionPoint;
	}
}

void Hero::KickCheck()
{
	ThornHitCheck();
	UpdateActionPoint();
	GetChapter()->M_UpdateHeroActionPoint();
}

void Hero::ChapterCameraPosUpdate(const FVector& _Diff)
{
	HitActor::ChapterCameraPosUpdate(_Diff);

	GetChapter()->CameraPosUpdate(_Diff);
}

void Hero::MoveStart()
{
	HeroBase::MoveStart();

	GetChapter()->M_ChangeThornState();
	UpdateActionPoint();
}

void Hero::KickStart()
{
	HeroBase::KickStart();

	GetChapter()->M_ChangeThornState();

	Point NextPoint = GetNextLocationPoint();
	HitActor* Other = GetChapter()->M_GetHitActor(NextPoint);
	Other->NextStateCheck(MoveDir);
}

void Hero::UpdateActionPoint()
{
	// Cheat
	if (true == GetCheatMode())
	{
		return;
	}

	--ActionPoint;
}
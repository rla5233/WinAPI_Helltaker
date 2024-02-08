#include "MoveActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EnginePlatform/EngineInput.h>

MoveActor::MoveActor()
{
	MoveDistanceX = ContentsHelper::GetTileScale().X;
	MoveDistanceY = ContentsHelper::GetTileScale().Y;
}

MoveActor::~MoveActor()
{}

void MoveActor::MoveOneBlock(float _DeltaTime)
{
	if (MoveDir == EActorMoveDir::Left || MoveDir == EActorMoveDir::Right)
	{
		if (0 < MoveDistanceX)
		{
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			MoveDistanceX -= Speed * _DeltaTime;	
		}
		else
		{
			LocationPoint += FMoveDir;

			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D()};
			SetActorLocation(dynamic_cast<ChapterManager*>(GetWorld())->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceX = ContentsHelper::GetTileScale().X;
			MoveOff();
		}
	}
	else if (MoveDir == EActorMoveDir::Up || MoveDir == EActorMoveDir::Down)
	{
		if (0 < MoveDistanceY)
		{
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			MoveDistanceY -= Speed * _DeltaTime;
		}
		else
		{
			LocationPoint += FMoveDir;

			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D() };
			SetActorLocation(dynamic_cast<ChapterManager*>(GetWorld())->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceY = ContentsHelper::GetTileScale().X;
			MoveOff();
		}
	}
}

void MoveActor::MoveDirChange(EActorMoveDir _Dir)
{
	MoveDir = _Dir;
}

void MoveActor::FMoveDirCheck()
{
	switch (MoveDir)
	{
	case EActorMoveDir::Left:
		FMoveDir = FVector::Left;
		break;
	case EActorMoveDir::Right:
		FMoveDir = FVector::Right;
		break;
	case EActorMoveDir::Up:
		FMoveDir = FVector::Up;
		break;
	case EActorMoveDir::Down:
		FMoveDir = FVector::Down;
		break;
	}
}

void MoveActor::SeeDirChange(EActorSeeDir _Dir)
{
	SeeDir = _Dir;
}

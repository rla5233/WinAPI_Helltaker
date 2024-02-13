#include "MoveActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EnginePlatform/EngineInput.h>

MoveActor::MoveActor()
{
	MoveDistanceX = ContentsHelper::GetTileScale().X;
	MoveDistanceY = ContentsHelper::GetTileScale().Y;
	Speed = ContentsHelper::GetWindowScale().X / 3.0f;
	FirstSpeed = ContentsHelper::GetWindowScale().X / 3.0f;
	Acceleration = ContentsHelper::GetWindowScale().X * 4.0f;
}

MoveActor::MoveActor(float _Speed, float _Acceleration)
	: Speed(_Speed), Acceleration(_Acceleration)
{
	MoveDistanceX = ContentsHelper::GetTileScale().X;
	MoveDistanceY = ContentsHelper::GetTileScale().Y;
	FirstSpeed = _Speed;
}

MoveActor::~MoveActor()
{}

void MoveActor::MoveOneBlock(float _DeltaTime)
{
	FMoveDirCheck();

	if (MoveDir == EMoveActorDir::Left || MoveDir == EMoveActorDir::Right)
	{
		if (0 < MoveDistanceX)
		{
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			MoveDistanceX -= Speed * _DeltaTime;	
			Speed += Acceleration * _DeltaTime;
		}
		else
		{
			LocationPoint += FMoveDir;
			Speed = FirstSpeed;

			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D()};
			SetActorLocation(GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceX = ContentsHelper::GetTileScale().X;
			MoveOff();
		}
	}
	else if (MoveDir == EMoveActorDir::Up || MoveDir == EMoveActorDir::Down)
	{
		if (0 < MoveDistanceY)
		{
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			MoveDistanceY -= Speed * _DeltaTime;
			Speed += Acceleration * _DeltaTime;
		}
		else
		{
			LocationPoint += FMoveDir;
			Speed = FirstSpeed;

			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D() };
			SetActorLocation(GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceY = ContentsHelper::GetTileScale().Y;
			MoveOff();
		}
	}
}

void MoveActor::MoveDirChange(EMoveActorDir _Dir)
{
	MoveDir = _Dir;
}

void MoveActor::FMoveDirCheck()
{
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		FMoveDir = FVector::Left;
		break;
	case EMoveActorDir::Right:
		FMoveDir = FVector::Right;
		break;
	case EMoveActorDir::Up:
		FMoveDir = FVector::Up;
		break;
	case EMoveActorDir::Down:
		FMoveDir = FVector::Down;
		break;
	}
}

void MoveActor::SeeDirChange(EActorSeeDir _Dir)
{
	SeeDir = _Dir;
}

ChapterManager* MoveActor::GetChapter()
{
	return dynamic_cast<ChapterManager*>(GetWorld());
}

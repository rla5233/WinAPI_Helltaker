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
	PMoveDirCheck();

	if (MoveDir == EMoveActorDir::Left || MoveDir == EMoveActorDir::Right)
	{
		if (0.0001f < MoveDistanceX)
		{
			FVector FMoveDir = FVector(PMoveDir.X, PMoveDir.Y);
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			MoveDistanceX -= Speed * _DeltaTime;	
			Speed += Acceleration * _DeltaTime;
		}
		else
		{
			LocationPoint += PMoveDir;
			Speed = FirstSpeed;

			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D()};
			SetActorLocation(GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceX = ContentsHelper::GetTileScale().X;
			MoveOff();
		}
	}
	else if (MoveDir == EMoveActorDir::Up || MoveDir == EMoveActorDir::Down)
	{
		if (0.0001f < MoveDistanceY)
		{
			FVector PrevLocation = GetActorLocation();
			FVector FMoveDir = FVector(PMoveDir.X, PMoveDir.Y);
			AddActorLocation(FMoveDir * Speed * _DeltaTime);
			FVector NextLocation = GetActorLocation();

			ChapterCameraPosUpdate(NextLocation - PrevLocation);
			MoveDistanceY -= Speed * _DeltaTime;
			Speed += Acceleration * _DeltaTime;
		}
		else
		{
			LocationPoint += PMoveDir;
			Speed = FirstSpeed;

			FVector PrevLocation = GetActorLocation();
			FVector hTileScale = { ContentsHelper::GetTileScale().Half2D() };
			SetActorLocation(GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale);
			MoveDistanceY = ContentsHelper::GetTileScale().Y;
			FVector NextLocation = GetActorLocation();

			ChapterCameraPosUpdate(NextLocation - PrevLocation);
			MoveOff();
		}
	}
}

void MoveActor::MoveDirChange(EMoveActorDir _Dir)
{
	MoveDir = _Dir;
}

void MoveActor::PMoveDirCheck()
{
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		PMoveDir = Point::Left;
		break;
	case EMoveActorDir::Right:
		PMoveDir = Point::Right;
		break;
	case EMoveActorDir::Up:
		PMoveDir = Point::Up;
		break;
	case EMoveActorDir::Down:
		PMoveDir = Point::Down;
		break;
	}
}

void MoveActor::SeeDirChange(EActorSeeDir _Dir)
{
	SeeDir = _Dir;
}

#pragma once
#include "RenderActor.h"

class ChapterManager;

class MoveActor : public RenderActor
{
public:
	// constructor destructor
	MoveActor();
	~MoveActor();

	// delete Function
	MoveActor(const MoveActor& _Other) = delete;
	MoveActor(MoveActor&& _Other) noexcept = delete;
	MoveActor& operator=(const MoveActor& _Other) = delete;
	MoveActor& operator=(MoveActor&& _Other) noexcept = delete;

	void MoveOneBlock(float _DeltaTime);

	void MoveDirChange(EActorMoveDir _Dir);
	void FMoveDirCheck();
	void SeeDirChange(EActorSeeDir _Dir);
	
	void SetLocationPoint(FVector _Point)
	{
		LocationPoint = _Point;
	}

	bool IsMove() const
	{
		return IsMoveValue;
	}

	void MoveOn()
	{
		IsMoveValue = true;
	}

	void MoveOff()
	{
		IsMoveValue = false;
	}

	FVector GetLocationPoint() const
	{
		return LocationPoint;
	}

	ChapterManager* GetChapter();

protected:
	EActorMoveDir MoveDir = EActorMoveDir::None;
	EActorSeeDir SeeDir = EActorSeeDir::None;

private:
	float MoveDistanceX = 0.0f;
	float MoveDistanceY = 0.0f;

	float Speed = 0.0f;
	FVector FMoveDir = FVector::Zero;
	bool IsMoveValue = false;

	FVector LocationPoint = FVector::Zero;
};

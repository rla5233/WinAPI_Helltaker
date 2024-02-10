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

	void MoveDirChange(EMoveActorDir _Dir);
	void FMoveDirCheck();
	void SeeDirChange(EActorSeeDir _Dir);
	


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

	EMoveActorType GetMoveActorType() const
	{
		return MoveActorType;
	}

	void SetMoveActorType(EMoveActorType _MoveActorType)
	{
		MoveActorType = _MoveActorType;
	}

	FVector GetLocationPoint() const
	{
		return LocationPoint;
	}

	void SetLocationPoint(FVector _Point)
	{
		LocationPoint = _Point;
	}

	FVector GetNextLocationPoint() const
	{
		return NextLocationPoint;
	}

	void SetNextLocationPoint(FVector _Point)
	{
		NextLocationPoint = _Point;
	}

	ChapterManager* GetChapter();

protected:
	EMoveActorDir MoveDir = EMoveActorDir::None;
	EActorSeeDir SeeDir = EActorSeeDir::None;

private:
	float MoveDistanceX = 0.0f;
	float MoveDistanceY = 0.0f;

	float Speed = 0.0f;
	FVector FMoveDir = FVector::Zero;
	bool IsMoveValue = false;

	FVector LocationPoint = FVector::Zero;
	FVector NextLocationPoint = FVector::Zero;

	EMoveActorType MoveActorType = EMoveActorType::None;
};

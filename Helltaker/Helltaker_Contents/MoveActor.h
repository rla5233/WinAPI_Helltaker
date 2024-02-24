#pragma once
#include "RenderActor.h"

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
	void MoveDirCheck();
	bool MoveEffectEndCheck();
	void AllMoveEffectActiveOff();
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

	Point GetLocationPoint() const
	{
		return CurLocationPoint;
	}

	void SetLocationPoint(Point _Point)
	{
		CurLocationPoint = _Point;
	}

	Point GetNextLocationPoint() const
	{
		return NextLocationPoint;
	}

	void SetNextLocationPoint(Point _Point)
	{
		NextLocationPoint = _Point;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void ChapterCameraPosUpdate(const FVector& _Diff) {};

	virtual void MoveStart();
	virtual void EffectPosUpdate(const FVector& _Diff);

	EMoveActorDir MoveDir = EMoveActorDir::None;
	EActorSeeDir SeeDir = EActorSeeDir::None;

private:
	void MovePosCheck();
	void CreateRandomMoveEffect();

private:
	std::list<UImageRenderer*> AllMoveEffectRenderer;
	static const float MoveEffectInter;

	float MoveTime = 0.0f;
	static const float MoveTimeWeight;
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	FVector FMoveDir = FVector::Zero;
	Point PMoveDir = Point::Zero;
	bool IsMoveValue = false;

	Point CurLocationPoint = { -1, -1 };
	Point NextLocationPoint = { -1, -1 };

	static bool IsLoad;
};

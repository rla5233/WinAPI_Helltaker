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
	void AllMoveEffectDestory();
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

	float GetMoveTime() const
	{
		return MoveTime;
	}

	static float GetMoveTimeWeight()
	{
		return MoveTimeWeight;
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

	Point GetPMoveDir() const
	{
		return PMoveDir;
	}

	EMoveActorDir GetMoveDir() const
	{
		return MoveDir;
	}

	EActorSeeDir GetSeeDir() const
	{
		return SeeDir;
	}

	void SetTargetPos(const FVector& _Pos)
	{
		TargetPos = _Pos;
	}

	void AddTargetPos(const FVector& _Pos)
	{
		TargetPos += _Pos;
	}

	void AddStartPos(const FVector& _Pos)
	{
		StartPos += _Pos;
	}

	const FVector& GetStartPos() const
	{
		return StartPos;
	}

	const FVector& GetFMoveDir() const
	{
		return FMoveDir;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void ThornHitCheck() {};

	virtual void MoveStart();
	virtual void EffectPosUpdate(const FVector& _Diff);

	void CreateRandomMoveEffect(EChapterType _ChapType = EChapterType::Default);
private:
	void MovePosCheck();

private:
	std::list<UImageRenderer*> AllMoveEffectRenderer;
	static const FVector MoveEffectScale;
	static const float MoveEffectInter;

	EMoveActorDir MoveDir = EMoveActorDir::None;
	EActorSeeDir SeeDir = EActorSeeDir::None;

	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	static const float MoveTimeWeight;

	FVector FMoveDir = FVector::Zero;
	Point PMoveDir = Point::Zero;
	bool IsMoveValue = false;

	Point CurLocationPoint = { -1, -1 };
	Point NextLocationPoint = { -1, -1 };

	static bool IsLoad;
};

#pragma once
#include "RenderActor.h"

class MoveActor : public RenderActor
{
public:
	// constructor destructor
	MoveActor();
	MoveActor(float _Speed, float _Acceleration);
	~MoveActor();

	// delete Function
	MoveActor(const MoveActor& _Other) = delete;
	MoveActor(MoveActor&& _Other) noexcept = delete;
	MoveActor& operator=(const MoveActor& _Other) = delete;
	MoveActor& operator=(MoveActor&& _Other) noexcept = delete;

	void MoveOneBlock(float _DeltaTime);

	void MoveDirChange(EMoveActorDir _Dir);
	void PMoveDirCheck();
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
		return LocationPoint;
	}

	void SetLocationPoint(Point _Point)
	{
		LocationPoint = _Point;
	}

	Point GetNextLocationPoint() const
	{
		return NextLocationPoint;
	}

	void SetNextLocationPoint(Point _Point)
	{
		NextLocationPoint = _Point;
	}

	void CreateMoveEffect();

	void SetRandomMoveEffect();

protected:
	virtual void BeginPlay() override;

	virtual void ChapterCameraPosUpdate(const FVector& _NextLocation) {};

	EMoveActorDir MoveDir = EMoveActorDir::None;
	EActorSeeDir SeeDir = EActorSeeDir::None;

private:
	UImageRenderer* EffectRenderer = nullptr;

	float MoveDistanceX = 0.0f;
	float MoveDistanceY = 0.0f;

	float FirstSpeed = 0.0f;
	float Speed = 0.0f;
	float Acceleration = 0.0f;
	Point PMoveDir = Point::Zero;
	bool IsMoveValue = false;

	Point LocationPoint = { -1, -1 };
	Point NextLocationPoint = { -1, -1 };

	static const float MoveInter;
	static bool IsLoad;
};

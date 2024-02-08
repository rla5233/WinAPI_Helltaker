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

	void MoveCheck(float _DeltaTime);
	void MoveOneBlock(float _DeltaTime);

	void SetLocationPoint(FVector _Point)
	{
		LocationPoint = _Point;
	}

protected:

private:
	float MoveDistanceX = 0.0f;
	float MoveDistanceY = 0.0f;

	float Speed = 500.0f;
	FVector MoveDir = FVector::Zero;
	FVector LocationPoint = FVector::Zero;

	bool IsMoving = false;
};

#pragma once
#include <EngineCore\Actor.h>

class MoveActor : public AActor
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
		StagePoint = _Point;
	}

protected:

private:
	float MoveDistance = 0.0f;
	float Speed = 500.0f;
	FVector MoveDir = FVector::Zero;
	FVector StagePoint = FVector::Zero;

	bool IsMoving = false;
};

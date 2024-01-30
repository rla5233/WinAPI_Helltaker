#pragma once
#include <EngineCore\Actor.h>

class MoveObject : public AActor
{
public:
	// constructor destructor
	MoveObject();
	~MoveObject();

	// delete Function
	MoveObject(const MoveObject& _Other) = delete;
	MoveObject(MoveObject&& _Other) noexcept = delete;
	MoveObject& operator=(const MoveObject& _Other) = delete;
	MoveObject& operator=(MoveObject&& _Other) noexcept = delete;

	void MoveCheck(float _DeltaTime);
	void MoveOneBlock(float _DeltaTime);

protected:

private:
	float MoveDistance = 0.0f;
	float Speed = 500.0f;
	FVector MoveDir = FVector::Zero;

	bool IsMoving = false;

};

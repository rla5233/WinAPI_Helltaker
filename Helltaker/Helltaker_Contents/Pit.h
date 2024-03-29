#pragma once

#include "SinMoveActor.h"

// ���� :
class Pit : public SinMoveActor
{
public:
	// constructor destructor
	Pit();
	~Pit();
	
	// delete Function
	Pit(const Pit& _Other) = delete;
	Pit(Pit&& _Other) noexcept = delete;
	Pit& operator=(const Pit& _Other) = delete;
	Pit& operator=(Pit&& _Other) noexcept = delete;
	
	static const FVector& GetScale()
	{
		return Scale;
	}

	void StateChange(ESinPitState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	static const FVector Scale;

	ESinPitState State = ESinPitState::None;
	static bool IsLoad;
};


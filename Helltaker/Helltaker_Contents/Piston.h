#pragma once

#include "SinMoveActor.h"

// Ό³Έν :
class Piston : public SinMoveActor
{
public:
	// constructor destructor
	Piston();
	~Piston();
	
	// delete Function
	Piston(const Piston& _Other) = delete;
	Piston(Piston&& _Other) noexcept = delete;
	Piston& operator=(const Piston& _Other) = delete;
	Piston& operator=(Piston&& _Other) noexcept = delete;

	ESinPistonState GetState() const
	{
		return State;
	}

	void SetType(ESinPistonType _Type)
	{
		Type = _Type;
	}

	void StateChange(ESinPistonState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);
	void Move1(float _DeltaTime);
	void Move2(float _DeltaTime);
	void Move3(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* LT_ImageRenderer = nullptr;
	UImageRenderer* RT_ImageRenderer = nullptr;

	UImageRenderer* LB_ImageRenderer = nullptr;
	UImageRenderer* RB_ImageRenderer = nullptr;
	static const FVector Scale;
	static const float TurnInter;
	static const float TurnDelayTime;
	float TimeCount = 0.0f;

	int MoveOrder = -1;

	ESinPistonType Type = ESinPistonType::None;
	ESinPistonState State = ESinPistonState::None;
	static bool IsLoad;
};


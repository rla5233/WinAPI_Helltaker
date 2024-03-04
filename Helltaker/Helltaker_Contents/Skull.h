#pragma once

#include "SinMoveActor.h"

// Ό³Έν :
class Skull : public SinMoveActor
{
public:
	// constructor destructor
	Skull();
	~Skull();
	
	// delete Function
	Skull(const Skull& _Other) = delete;
	Skull(Skull&& _Other) noexcept = delete;
	Skull& operator=(const Skull& _Other) = delete;
	Skull& operator=(Skull&& _Other) noexcept = delete;

	void StateChange(ESinSkullState _State, const FVector& _MoveDistance = FVector::Zero);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart(const FVector& _MoveDistance);
	void Move(float _DeltaTime);

	void SetSkull();
	void SetArm();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* LB_SkullRenderer = nullptr;
	UImageRenderer* RB_SkullRenderer = nullptr;
	UImageRenderer* LT_SkullRenderer = nullptr;
	UImageRenderer* RT_SkullRenderer = nullptr;
	static const FVector SkullScale;

	UImageRenderer* L_ArmRenderer = nullptr;
	UImageRenderer* R_ArmRenderer = nullptr;
	static const FVector ArmScale;

	ESinSkullState State = ESinSkullState::None;
	static bool IsLoad;
};


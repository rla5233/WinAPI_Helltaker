#pragma once

#include "SinComponent.h"

// Ό³Έν :
class Skull : public SinComponent
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


	void StateChange(ESinSkullState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* LB_SkullRenderer = nullptr;
	UImageRenderer* RB_SkullRenderer = nullptr;
	UImageRenderer* LT_SkullRenderer = nullptr;
	UImageRenderer* RT_SkullRenderer = nullptr;

	UImageRenderer* L_ArmRenderer = nullptr;
	UImageRenderer* R_ArmRenderer = nullptr;

	ESinSkullState State = ESinSkullState::None;
	static bool IsLoad;
};


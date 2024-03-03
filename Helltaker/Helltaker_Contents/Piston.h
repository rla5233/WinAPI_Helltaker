#pragma once

#include "SinComponent.h"

// Ό³Έν :
class Piston : public SinComponent
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

	void StateChange(ESinPistonState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);
	
	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* LT_ImageRenderer = nullptr;
	UImageRenderer* RT_ImageRenderer = nullptr;

	UImageRenderer* LB_ImageRenderer = nullptr;
	UImageRenderer* RB_ImageRenderer = nullptr;


	ESinPistonState State = ESinPistonState::None;
	static bool IsLoad;
};


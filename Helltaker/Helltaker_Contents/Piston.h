#pragma once

#include "SinComponent.h"

// ���� :
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
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;


	ESinPistonState State = ESinPistonState::None;
	static bool IsLoad;
};


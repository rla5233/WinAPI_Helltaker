#pragma once

#include "SinComponent.h"

// Ό³Έν :
class Pit : public SinComponent
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

	void StateChange(ESinPitState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:


	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	static const FVector SinPitScale;
	static const float SinPitSpeedY;

	ESinPitState State = ESinPitState::None;
	static bool IsLoad;
};


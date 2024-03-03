#pragma once

#include "SinComponent.h"

// Ό³Έν :
class Chain : public SinComponent
{
public:
	// constructor destructor
	Chain();
	~Chain();
	
	// delete Function
	Chain(const Chain& _Other) = delete;
	Chain(Chain&& _Other) noexcept = delete;
	Chain& operator=(const Chain& _Other) = delete;
	Chain& operator=(Chain&& _Other) noexcept = delete;

	void StateChange(ESinChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	static const FVector SinChainSCale;
	static const float SinChainSpeedY;

	ESinChainState State = ESinChainState::None;
	static bool IsLoad;
};


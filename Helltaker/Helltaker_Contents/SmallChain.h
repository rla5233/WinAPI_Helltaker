#pragma once

#include "SinMoveActor.h"

// Ό³Έν :
class SmallChain : public SinMoveActor
{
public:
	// constructor destructor
	SmallChain();
	~SmallChain();

	// delete Function
	SmallChain(const SmallChain& _Other) = delete;
	SmallChain(SmallChain&& _Other) noexcept = delete;
	SmallChain& operator=(const SmallChain& _Other) = delete;
	SmallChain& operator=(SmallChain&& _Other) noexcept = delete;

	void StateChange(ESinSmallChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;

	ESinSmallChainType Type = ESinSmallChainType::None;
	ESinSmallChainState State = ESinSmallChainState::None;
	static bool IsLoad;
};

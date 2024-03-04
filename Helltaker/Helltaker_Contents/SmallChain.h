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

	void StateChange();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;

	static bool IsLoad;
};

#pragma once

#include "SinMoveActor.h"

// Ό³Έν :
class HitChain : public SinMoveActor
{
public:
	// constructor destructor
	HitChain();
	~HitChain();

	// delete Function
	HitChain(const HitChain& _Other) = delete;
	HitChain(HitChain&& _Other) noexcept = delete;
	HitChain& operator=(const HitChain& _Other) = delete;
	HitChain& operator=(HitChain&& _Other) noexcept = delete;

	void StateChange(ESinHitChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void DeathStart();
	void Death(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	std::list<UImageRenderer*> EffectRenderer;
	const FVector Scale;

	ESinHitChainState State = ESinHitChainState::None;
	static bool IsLoad;
};

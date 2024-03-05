#pragma once

#include "SinMoveActor.h"

// ���� :
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

	void SetType(ESinHitChainType _Type)
	{
		Type = _Type;
	}

	void StateChange(ESinHitChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void DeathStart();
	void Death(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	std::list<UImageRenderer*> AllHitEffectRenderer;
	static const FVector Scale;

	ESinHitChainType Type = ESinHitChainType::None;
	ESinHitChainState State = ESinHitChainState::None;
	static bool IsLoad;
};

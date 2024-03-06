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

	void SetPhase(ESinPhase _Phase)
	{
		Phase = _Phase;
	};

	void SetPhase1_Idx(int _Index)
	{
		Phase1_Idx = _Index;
	}

	void StateChange(ESinSmallChainState _State);
	void CreateImageRenderer(ESinSmallChainType _Type);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void ShowStart();
	void Show(float _DeltaTime);
	
	void ShowAnimation(float _DeltaTime);
	void VerShowAnimation(float _DeltaTime);
	void HorShowAnimation(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void DeathStart();
	void Death(float _DeltaTime);

	void HitAnimation(float _DeltaTime);
	void VerHitAnimation(float _DeltaTime);
	void HorHitAnimation(float _DeltaTime);
	void HeroHitCheck(float _DeltaTime);

	void MoveY_Update(float _DeltaTime);
	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	static const FVector V_Scale;
	static const FVector H_Scale;
	
	bool IsShow = false;
	bool IsHit = false;
	float TimeCount = 0.0f;

	static const float HitTime;
	float HitTimeCount = 0.0f;

	int Phase1_Idx = -1;
	ESinPhase Phase = ESinPhase::None;
	ESinSmallChainType Type = ESinSmallChainType::None;
	ESinSmallChainState State = ESinSmallChainState::None;
	static bool IsLoad;
};

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

	void SetType(ESinHitChainType _Type)
	{
		Type = _Type;
	}

	void SetCurPoint(SinTile _Point)
	{
		CurPoint = _Point;
	}

	SinTile GetCurPoint() const
	{
		return CurPoint;
	}

	int GetHitCount() const
	{
		return HitCount;
	}

	bool IsCanHit() const
	{
		return CanHit;
	}

	void StateChange(ESinHitChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void FadeInCheck(float _DeltaTime);
	void FadeOutCheck(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void DeathStart();
	void Death(float _DeltaTime);

	void HitDelayCheck(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	std::list<UImageRenderer*> AllHitEffectRenderer;
	static const FVector Scale;

	int IdleOrder = -1;

	int HitCount = 6;
	static const float HitDelayTime;
	float HitDelayTimeCount = 0.0f;
	bool CanHit = true;

	SinTile CurPoint = { 0, 0 };
	ESinHitChainType Type = ESinHitChainType::None;
	ESinHitChainState State = ESinHitChainState::None;
	static bool IsLoad;
};
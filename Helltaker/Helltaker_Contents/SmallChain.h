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
	void CreateImageRenderer(ESinSmallChainType _Type);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void ShowStart();
	void Show(float _DeltaTime);

	void ShowAnimation(float _DeltaTime);
	void VerShowAnimation(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void HitAnimation(float _DeltaTime);
	void VerHitAnimation(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	static const FVector V_Scale;
	static const FVector H_Scale;
	static const float SpeedY;

	bool IsShow = false;
	bool IsHit = false;
	float TimeCount = 0.0f;

	ESinSmallChainType Type = ESinSmallChainType::None;
	ESinSmallChainState State = ESinSmallChainState::None;
	static bool IsLoad;
};

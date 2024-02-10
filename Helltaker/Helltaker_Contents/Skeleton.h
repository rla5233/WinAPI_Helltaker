#pragma once
#include "MoveActor.h"

// Ό³Έν :
class Skeleton : public MoveActor
{
public:
	// constructor destructor
	Skeleton();
	~Skeleton();

	// delete Function
	Skeleton(const Skeleton& _Other) = delete;
	Skeleton(Skeleton&& _Other) noexcept = delete;
	Skeleton& operator=(const Skeleton& _Other) = delete;
	Skeleton& operator=(Skeleton&& _Other) noexcept = delete;

	void Idle(float _DeltaTime);
	void IdleStart();
	void Hit(float _DeltaTime);
	void HitStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void StateUpdate(float _DeltaTime);
	void StateChange(ESkeletonState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector HitScale = { 0.9f, 0.9f };
	const float HitInter = 0.07f;

	ESkeletonState State = ESkeletonState::None;
};

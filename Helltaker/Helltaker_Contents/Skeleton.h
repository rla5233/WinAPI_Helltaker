#pragma once
#include "HitActor.h"

// Ό³Έν :
class Skeleton : public HitActor
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

	void Idle(float _DeltaTime) ;
	void IdleStart() ;
	void Hit(float _DeltaTime) ;
	void HitStart(EMoveActorDir _OtherMoveDir) ;
	void Move(float _DeltaTime);
	void MoveStart() override;
	void Death(float _DeltaTime) ;
	void DeathStart();

protected:
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(Point _Point) override;

    void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) override;
	void StateUpdate(float _DeltaTime) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector HitScale = { 0.9f, 0.9f };
	const float HitInter = 0.04f;

	static bool IsLoad;
};

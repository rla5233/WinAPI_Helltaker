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

	void IdleStart() ;
	void Idle(float _DeltaTime) ;
	void HitStart(EMoveActorDir _OtherMoveDir) ;
	void Hit(float _DeltaTime) ;
	void HitMoveEnd(float _DeltaTime);
	void DeathStart();
	void Death(float _DeltaTime) ;

protected:
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(int _X, int _Y) override;

    void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) override;
	void StateUpdate(float _DeltaTime) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector HitScale = { 0.9f, 0.9f };
	const float HitInter = 0.04f;

	static bool IsLoad;
};

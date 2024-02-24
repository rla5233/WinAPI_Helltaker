#pragma once
#include "HitActor.h"

// ���� :
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

	void Idle(float _DeltaTime);
	void IdleStart();
	void Hit(float _DeltaTime);
	void HitStart();
	void Move(float _DeltaTime);
	void MoveStart() override;
	void Death(float _DeltaTime);
	void DeathStart();

protected:
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(Point _Point);

    void StateChange(EHitActorState _State);
	void StateUpdate(float _DeltaTime);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	static const FVector IdleScale;
	static const float IdleInter;
	
	static const FVector HitScale;
	static const float HitInter;

	static bool IsLoad;
};

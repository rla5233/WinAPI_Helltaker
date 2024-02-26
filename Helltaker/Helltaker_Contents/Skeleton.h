#pragma once
#include "HitActor.h"

class DeathParticle;

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Hit(float _DeltaTime);
	void HitStart();
	void Move(float _DeltaTime);
	void MoveStart() override;
	void Death(float _DeltaTime);
	void DeathStart();
	
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(Point _Point);
	
	void StateUpdate(float _DeltaTime);
    void StateChange(EHitActorState _State);

	void DeathParticleMoveUpdate(float _DeltaTime);
	void CreateRandomDeathParicle();
	
private:
	UImageRenderer* ImageRenderer = nullptr;

	static const FVector IdleScale;
	static const float IdleInter;
	
	static const FVector HitScale;
	static const float HitInter;

	std::list<DeathParticle> AllDeathParticle;
	static const int DeathParticleCount;

	static bool IsLoad;
};

class DeathParticle
{
	friend Skeleton;
public:
	void DeathParticleMove(float _DeltaTime);

private:
	UImageRenderer* DeathParticleRenderer = nullptr;
	FVector Speed = FVector::Zero;

	static const FVector Scale;
};
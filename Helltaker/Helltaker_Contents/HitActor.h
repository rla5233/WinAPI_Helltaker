#pragma once

#include "MoveActor.h"

// Ό³Έν :
class HitActor : public MoveActor
{
public:
	// constructor destructor
	HitActor();
	~HitActor();
	
	// delete Function
	HitActor(const HitActor& _Other) = delete;
	HitActor(HitActor&& _Other) noexcept = delete;
	HitActor& operator=(const HitActor& _Other) = delete;
	HitActor& operator=(HitActor&& _Other) noexcept = delete;

	void HitActorInfoUpdate(EHitActorState _NextState);

	void SetHitActorState(EHitActorState _State)
	{
		State = _State;
	}

	EHitActorState GetHitActorState() const
	{
		return State;
	}

	void InformDestroytoChapter();

	void CreateBigHitEffect();
	void CreateSmallHitEffect();

	void SetRandomBigHitEffect();
	void SetRandomSmallHitEffect();

	bool HitEffectEndCheck();
	void EffectPosUpdate(const FVector& _Diff) override;

	virtual void NextStateCheck(EMoveActorDir _OtherMoveDir) {};
protected:
	virtual void BeginPlay() override;

	virtual void NextTileCheck(Point _Point) {};
	virtual void StateUpdate(float _DeltaTime) {};
	virtual void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) {};

	virtual void Hit(float _DeltaTime) {};
	virtual void HitStart() {};

private:
	UImageRenderer* EffectRenderer = nullptr;
	
	EHitActorState State = EHitActorState::None;

	static const float BigHitInter;
	static const float SmallHitInter;
	static bool IsLoad;
};


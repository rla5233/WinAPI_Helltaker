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

	void CreateHitEffect();
	void CreateBigHitEffect();
	void CreateSmallHitEffect();

	void SetRandomBigHitEffect();
	void SetRandomSmallHitEffect();

	bool HitEffectEndCheck();
	bool AllEffectEndCheck();
	void EffectPosUpdate(const FVector& _Diff) override;

	virtual void NextStateCheck(EMoveActorDir _OtherMoveDir) {};
protected:
	virtual void BeginPlay() override;

private:
	UImageRenderer* EffectRenderer = nullptr;
	
	EHitActorState State = EHitActorState::None;

	static const float BigHitInter;
	static const float SmallHitInter;
	static bool IsLoad;
};


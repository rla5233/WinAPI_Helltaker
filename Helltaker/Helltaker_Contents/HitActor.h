#pragma once

#include "MoveActor.h"

// ���� :
class HitActor : public MoveActor
{
public:
	// constructor destructor
	HitActor();
	HitActor(float _Speed, float _Acceleration);
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

	bool HitEffectEndCheck();

	virtual void NextStateCheck(EMoveActorDir _OtherMoveDir) {};
protected:
	virtual void NextTileCheck(Point _Point) {};
	virtual void StateUpdate(float _DeltaTime) {};
	virtual void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) {};

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) {};

private:
	UImageRenderer* EffectRenderer = nullptr;
	
	EHitActorState State = EHitActorState::None;

	static const float BigHitInter;
	static const float SmallHitInter;
	static bool IsLoad;
};


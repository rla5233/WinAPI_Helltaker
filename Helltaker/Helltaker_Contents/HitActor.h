#pragma once

#include "MoveActor.h"

// Ό³Έν :
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


	virtual void NextStateCheck(EMoveActorDir _OtherMoveDir) {};

protected:
	virtual void NextTileCheck(Point _Point) {};
	virtual void StateUpdate(float _DeltaTime) {};
	virtual void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) {};

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

private:
	EHitActorState State = EHitActorState::None;
};


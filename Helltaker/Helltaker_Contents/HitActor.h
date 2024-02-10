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

	void SetHitActorState(EHitActorState _State)
	{
		State = _State;
	}

	EHitActorState GetHitActorState() const
	{
		return State;
	}

	virtual void NextTileCheck(int _X, int _Y) {};
	virtual void StateUpdate(float _DeltaTime) {};
	virtual void StateChange(EHitActorState _State, EActorMoveDir _OtherMoveDir = EActorMoveDir::None) {};

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

protected:

private:
	EHitActorState State = EHitActorState::None;
};


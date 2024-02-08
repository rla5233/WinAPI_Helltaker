#pragma once
#include "MoveActor.h"

class Hero : public MoveActor
{
public:
	// constrcuter destructer
	Hero();
	~Hero();

	// delete Function
	Hero(const Hero& _Other) = delete;
	Hero(Hero&& _Other) noexcept = delete;
	Hero& operator=(const Hero& _Other) = delete;
	Hero& operator=(Hero&& _Other) noexcept = delete;

	void Idle(float _DeltaTime);
	void IdleStart();
	void Move(float _DeltaTime);
	void MoveStart();
	void Kick(float _DeltaTime);
	void KickStart();
	void Victory(float _DeltaTime);
	void VictoryStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void ActionCheck(float _DeltaTime);
	

	void StateUpdate(float _DeltaTime);
	void StateChange(EHeroState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int ActionPoint = 25;

	EHeroState State = EHeroState::None;
};
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

	void ActionCheck();
	void NextTileCheck(int _X, int _Y);

	void StateUpdate(float _DeltaTime);
	void StateChange(EHeroState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int ActionPoint = 25;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector MoveScale = { 0.9f, 0.9f };
	const float MoveInter = 0.07f;

	const FVector KickScale = { 0.95f, 0.95f };
	const float KickInter = 0.07f;
	const float KickTime = KickInter * 13;
	float KickTimeCount = KickTime;

	const FVector VictoryScale = { 0.9f, 1.2f };
	const float VictoryInter = 0.15f;
	const float VictoryTime = VictoryInter * 17;
	float VictoryTimeCount = VictoryTime;

	EHeroState State = EHeroState::None;
};
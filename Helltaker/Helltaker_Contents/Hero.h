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

	int GetActionPoint() const
	{
		return ActionPoint;
	}

	void SetActionPoint(int _Value)
	{
		ActionPoint = _Value;
	}

	EHeroState GetHeroState() const
	{
		return State;
	}

	UImageRenderer* GetImageRenderer()
	{
		return ImageRenderer;
	}

	
	void StateChange(EHeroState _State, float _DeltaTime = 0, int _Key1 = 0, int _Key2 = 0);

	// Debug
	void UpdateActionPoint();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Move(float _DeltaTime);
	void MoveStart(float _DeltaTime);
	void Kick(float _DeltaTime);
	void KickStart(float _DeltaTime, int _Key1, int _Key2);
	void Victory(float _DeltaTime);
	void VictoryStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void InputCheck(float _DeltaTime);
	void ThornHitCheck(EHeroState _State);
	void ActionCheck(float _DeltaTime, int _Key1, int _Key2);
	void NextTileCheck(int _X, int _Y, float _DeltaTime, int _Key1, int _Key2);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	int ActionPoint = -1;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector MoveScale = { 0.9f, 0.9f };
	const float MoveInter = 0.02f;

	const FVector KickScale = { 0.95f, 0.95f };
	const float KickInter = 0.016f;

	const float KickDelayTime = 0.01f;
	float KickDelayTimeCount = 0.0f;

	const float DeathInter = 0.05f;

	const FVector VictoryScale = { 0.9f, 1.2f };
	const float VictoryInter = 0.1f;
	
	bool CanActionCheck = false;
	EHeroState State = EHeroState::None;
	static bool IsLoad;


	bool CheatMode = false;
};
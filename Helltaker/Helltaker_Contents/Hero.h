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
	void MoveStart(float _DeltaTime);
	void Kick(float _DeltaTime);
	void KickStart(float _DeltaTime, int _Key1, int _Key2);
	void Victory(float _DeltaTime);
	void VictoryStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void InputCheck(float _DeltaTime);
	void ActionCheck(float _DeltaTime, int _Key1, int _Key2);
	void NextTileCheck(int _X, int _Y, float _DeltaTime, int _Key1, int _Key2);

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

	void StateUpdate(float _DeltaTime);
	void StateChange(EHeroState _State, float _DeltaTime = 0, int _Key1 = 0, int _Key2 = 0);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;
	int ActionPoint = -1;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.07f;

	const FVector MoveScale = { 0.9f, 0.9f };
	const float MoveInter = 0.02f;
	const float MoveTime = MoveInter * 6;
	float MoveTimeCount = MoveTime;

	const FVector KickScale = { 0.95f, 0.95f };
	const float KickInter = 0.016f;

	const float KickDelayTime = 0.01f;
	float KickDelayTimeCount = 0.0f;

	const float DeathInter = 0.05f;

	const FVector VictoryScale = { 0.9f, 1.2f };
	const float VictoryInter = 0.15f;
	const float VictoryTime = VictoryInter * 17;
	float VictoryTimeCount = VictoryTime;

	bool CanActionCheck = false;
	EHeroState State = EHeroState::None;
	static bool IsLoad;
};
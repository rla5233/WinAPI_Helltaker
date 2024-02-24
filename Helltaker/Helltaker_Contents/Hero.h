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

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	
	void StateChange(EHeroState _State, float _DeltaTime = 0, int _Key1 = 0, int _Key2 = 0);

	// Debug
	void UpdateActionPoint();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChapterCameraPosUpdate(const FVector& _Diff) override;

private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Move(float _DeltaTime);
	void MoveStart() override;
	void Kick(float _DeltaTime);
	void KickStart(float _DeltaTime, int _Key1, int _Key2);
	void Victory(float _DeltaTime);
	void VictoryStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void InputCheck(float _DeltaTime);
	void ThornHitCheck(EHeroState _State);
	void ActionCheck(float _DeltaTime, int _Key1, int _Key2);
	void NextTileCheck(Point _Point, float _DeltaTime, int _Key1, int _Key2);

	void CreateRandomHitEffect();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	std::list<UImageRenderer*> AllHitEffectRenderer;
	static const float HitInter;

	int ActionPoint = -1;
	bool IsHaveKey = false;

	static const FVector IdleScale;
	static const float IdleInter;

	static const FVector MoveScale;
	static const float MoveInter;

	static const FVector KickScale;
	static const float KickInter;

	static const float KickDelayTime;
	float KickDelayTimeCount = 0.0f;

	static const float DeathInter;

	static const FVector VictoryScale;
	static const float VictoryInter;
	
	bool CanActionCheck = false;
	EHeroState State = EHeroState::None;
	static bool IsLoad;

	bool CheatMode = false;
};
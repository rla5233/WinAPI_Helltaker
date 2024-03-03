#pragma once

#include "HitActor.h"

// Ό³Έν :
class HeroBase : public HitActor
{
public:
	// constructor destructor
	HeroBase();
	~HeroBase();
	
	// delete Function
	HeroBase(const HeroBase& _Other) = delete;
	HeroBase(HeroBase&& _Other) noexcept = delete;
	HeroBase& operator=(const HeroBase& _Other) = delete;
	HeroBase& operator=(HeroBase&& _Other) noexcept = delete;

	bool GetCanActionCheck() const
	{
		return CanActionCheck;
	}

	void SetCanActionCheck(bool _Value)
	{
		CanActionCheck = _Value;
	}

	EHeroState GetHeroState() const
	{
		return State;
	}

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	bool GetCheatMode() const
	{
		return CheatMode;
	}

	void AllEffectActiveOff();

	void StateChange(EHeroState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void MoveStart() override;
	
	virtual void KickStart();
	
	virtual void ActionCheck() {};
	virtual void KickCheck() {};
	
	void CreateRandomHitEffect();

private:
	void IdleStart();
	void Idle(float _DeltaTime);
	
	void Move(float _DeltaTime);
	
	void Kick(float _DeltaTime);
	
	void VictoryStart();
	void Victory(float _DeltaTime);

	void DeathStart();
	void Death(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

	void InputCheck(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;

	bool CanActionCheck = false;

	static const FVector IdleScale;
	static const float IdleInter;

	static const FVector MoveScale;
	static const float MoveInter;

	static const FVector KickScale;
	static const float KickInter;

	static const FVector HitScale;
	static const float HitInter;
	static const float DeathInter;

	static const FVector VictoryScale;
	static const float VictoryInter;

	EHeroState State = EHeroState::None;

	bool CheatMode = false;
	static bool IsLoad;
};
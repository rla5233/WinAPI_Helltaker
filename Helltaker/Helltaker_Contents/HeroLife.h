#pragma once

#include "RenderActor.h"

// Ό³Έν :
class HeroLife : RenderActor
{
public:
	// constructor destructor
	HeroLife();
	~HeroLife();
	
	// delete Function
	HeroLife(const HeroLife& _Other) = delete;
	HeroLife(HeroLife&& _Other) noexcept = delete;
	HeroLife& operator=(const HeroLife& _Other) = delete;
	HeroLife& operator=(HeroLife&& _Other) noexcept = delete;

	void StateChange(ESinHeroLifeState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::vector<UImageRenderer*> PyreRenderer;
	

	std::vector<UImageRenderer*> FireRenderer;
	static const float SinFireInter;

	ESinHeroLifeState State = ESinHeroLifeState::None;
	static bool IsLoad;
};


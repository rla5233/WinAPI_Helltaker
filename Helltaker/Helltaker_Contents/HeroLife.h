#pragma once

#include "RenderActor.h"

// Ό³Έν :
class HeroLife : public RenderActor
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
	
	void SetPanel();
	void SetEye();
	void SetPyre();
	void SetFire();

	void HitStart();
	void Hit(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_PanelRenderer = nullptr;
	UImageRenderer* R_PanelRenderer = nullptr;
	static const FVector PanelScale;

	UImageRenderer* EyeRenderer = nullptr;
	static const FVector EyeScale;
	
	std::vector<UImageRenderer*> PyreRenderer;
	static const FVector PyreScale;

	std::vector<UImageRenderer*> FireRenderer;
	static const FVector FireScale;
	static const float FireInter;

	ESinHeroLifeState State = ESinHeroLifeState::None;
	static bool IsLoad;
};


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

	void SetSinChapterNum(int _Number)
	{
		SinChapterNum = _Number;
	}

	void WheelTurnOn()
	{
		IsWheelTurn = true;
	}

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
	void SetWheel();

	void WheelTurnUpdate(float _DeltaTime);

	void HeroHitStart();
	void HeroHit(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_PanelRenderer = nullptr;
	UImageRenderer* R_PanelRenderer = nullptr;
	static const FVector PanelScale;

	UImageRenderer* WheelRenderer = nullptr;
	int SinChapterNum = -1;
	static const FVector WheelScale;
	bool IsWheelTurn = false;
	float TurnTime = 0.0f;
	float StartAngle = 0.0f;
	float TargetAngle = 0.0f;

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


#pragma once

#include "RenderActor.h"

// Ό³Έν :
class HitChainHp : public RenderActor
{
public:
	// constructor destructor
	HitChainHp();
	~HitChainHp();

	// delete Function
	HitChainHp(const HitChainHp& _Other) = delete;
	HitChainHp(HitChainHp&& _Other) noexcept = delete;
	HitChainHp& operator=(const HitChainHp& _Other) = delete;
	HitChainHp& operator=(HitChainHp&& _Other) noexcept = delete;

	void SetTotalHitCount(int _Count)
	{
		TotalHitCount = _Count * 6;
	}

	UImageRenderer* GetTextRenderer() const
	{
		return TextRenderer;
	}

	void StateChange(ESinHitChainHpState _State);
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);
	
	void HitStart();
	void Hit(float _DeltaTime);
	
	void DeathStart();
	void Death(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	UImageRenderer* Hp_Renderer = nullptr;
	UImageRenderer* TextRenderer = nullptr;
	static const FVector HpScale;
	static const FVector ImageScale;

	int TotalHitCount = 0;
	ESinHitChainHpState State = ESinHitChainHpState::None;
};

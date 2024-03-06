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



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	UImageRenderer* Hp_Renderer = nullptr;
	UImageRenderer* TextRenderer = nullptr;

};

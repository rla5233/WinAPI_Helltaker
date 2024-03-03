#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Shield : public RenderActor
{
public:
	// constructor destructor
	Shield();
	~Shield();
	
	// delete Function
	Shield(const Shield& _Other) = delete;
	Shield(Shield&& _Other) noexcept = delete;
	Shield& operator=(const Shield& _Other) = delete;
	Shield& operator=(Shield&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SetShield();

private:
	UImageRenderer* LB_ImageRenderer = nullptr;
	UImageRenderer* RB_ImageRenderer = nullptr;
	static const FVector B_Scale;

	UImageRenderer* LT_ImageRenderer = nullptr;
	UImageRenderer* RT_ImageRenderer = nullptr;
	static const FVector T_Scale;

	UImageRenderer* ShadowRenderer = nullptr;
	static const FVector Shadow_Scale;

	static bool IsLoad;
};


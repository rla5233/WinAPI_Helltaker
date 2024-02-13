#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Devil : public RenderActor
{
public:
	// constructor destructor
	Devil();
	~Devil();

	// delete Function
	Devil(const Devil& _Other) = delete;
	Devil(Devil&& _Other) noexcept = delete;
	Devil& operator=(const Devil& _Other) = delete;
	Devil& operator=(Devil&& _Other) noexcept = delete;
	
	void IdleStart();
	void Idle(float _DeltaTime);

	void VictoryStart();

	void StateChange(EDevilState _State);
	void StateUpdate(float _DeltaTime);	

	void SetDevil(std::string_view _Name);
	void LoveSignAnimation(float _DeltaTime);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* LoveSignRenderer = nullptr;
	const FVector LoveSignScale = { 0.3f, 0.4f };
	float LoveSignMove = 0.0f;
	float LoveSignSpeed = 28.0f;
	bool IsUp = true;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.082f;
	
	EDevilState State = EDevilState::None;
	static bool IsLoad;
};

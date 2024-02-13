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

	void StateChange(EDevilState _State);
	void StateUpdate(float _DeltaTime);	

	void SetDevil(std::string_view _Name);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const FVector IdleScale = { 0.9f, 0.9f };
	const float IdleInter = 0.082f;
	
	EDevilState State = EDevilState::None;
	static bool IsLoad;
};

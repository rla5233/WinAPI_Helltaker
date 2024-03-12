#pragma once

#include "RenderActor.h"

// Ό³Έν :
class SuccessSkel : public RenderActor
{
public:
	// constructor destructor
	SuccessSkel();
	~SuccessSkel();

	// delete Function
	SuccessSkel(const SuccessSkel& _Other) = delete;
	SuccessSkel(SuccessSkel&& _Other) noexcept = delete;
	SuccessSkel& operator=(const SuccessSkel& _Other) = delete;
	SuccessSkel& operator=(SuccessSkel&& _Other) noexcept = delete;

	void StateChange(ESinSkelState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StartStart();
	void Start();

	void IdleStart();
	void Idle();

private:
	void StateUpdate();

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;

	static const FVector Scale;
	static const float PosX;
	static const float SuccessInter;
	static const float IdleInter;

	ESinSkelState State = ESinSkelState::None;
	static bool IsLoad;
};

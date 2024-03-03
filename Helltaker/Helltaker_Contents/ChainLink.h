#pragma once

#include "SinComponent.h"

// Ό³Έν :
class ChainLink : public SinComponent
{
public:
	// constructor destructor
	ChainLink();
	~ChainLink();
	
	// delete Function
	ChainLink(const ChainLink& _Other) = delete;
	ChainLink(ChainLink&& _Other) noexcept = delete;
	ChainLink& operator=(const ChainLink& _Other) = delete;
	ChainLink& operator=(ChainLink&& _Other) noexcept = delete;

	static const FVector& GetScale()
	{
		return Scale;
	}

	void StateChange(ESinChainState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	static const FVector Scale;
	static const float SpeedY;

	ESinChainState State = ESinChainState::None;
	static bool IsLoad;
};


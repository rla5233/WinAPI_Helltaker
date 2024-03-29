#pragma once

#include "SinMoveActor.h"

// ���� :
class Bridge : public SinMoveActor
{
public:
	// constructor destructor
	Bridge();
	~Bridge();
	
	// delete Function
	Bridge(const Bridge& _Other) = delete;
	Bridge(Bridge&& _Other) noexcept = delete;
	Bridge& operator=(const Bridge& _Other) = delete;
	Bridge& operator=(Bridge&& _Other) noexcept = delete;

	static const FVector& GetScale()
	{
		return Scale;
	}

	void StateChange(ESinBridgeState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);
	void MoveY_Update(float _DeltaTime);
	
	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	static const FVector Scale;

	ESinBridgeState State = ESinBridgeState::None;
	static bool IsLoad;
};


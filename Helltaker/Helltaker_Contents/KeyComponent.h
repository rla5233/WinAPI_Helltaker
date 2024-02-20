#pragma once

#include "RenderActor.h"

// Ό³Έν :
class KeyComponent : public RenderActor
{
public:
	// constructor destructor
	KeyComponent();
	~KeyComponent();

	// delete Function
	KeyComponent(const KeyComponent& _Other) = delete;
	KeyComponent(KeyComponent&& _Other) noexcept = delete;
	KeyComponent& operator=(const KeyComponent& _Other) = delete;
	KeyComponent& operator=(KeyComponent&& _Other) noexcept = delete;

	void SetKeyComponentType(EKeyComponentType _Type)
	{
		Type = _Type;
	}

	void StateChange(EKeyComponentState _State);
private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Death(float _DeltaTime);
	void DeathStart();

	void StateUpdate(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	EKeyComponentState State = EKeyComponentState::None;
	EKeyComponentType Type = EKeyComponentType::None;

	static const FVector IdleScale;
	static const float IdleInter;
	static bool IsLoad;
};

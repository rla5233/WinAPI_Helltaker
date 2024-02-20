#pragma once

#include "HitActor.h"

// Ό³Έν :
class KeyComponent : public HitActor
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

	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;

	void StateChange(EKeyComponentState _State);

private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Death(float _DeltaTime);
	void DeathStart();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	EKeyComponentState State = EKeyComponentState::None;
	EKeyComponentType Type = EKeyComponentType::None;

	static const float IdleInter;
	static bool IsLoad;
};

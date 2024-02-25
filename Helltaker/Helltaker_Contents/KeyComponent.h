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

	void Hit(float _DeltaTime);
	void HitStart();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* EffectRenderer = nullptr;

	EKeyComponentState State = EKeyComponentState::None;
	EKeyComponentType Type = EKeyComponentType::None;

	static const FVector KeyScale;
	static const FVector LockBoxScale;

	static const float Key_IdleInter;

	static const FVector Death_EffectScale;
	static const float Death_EffectInter;

	static bool IsLoad;
};

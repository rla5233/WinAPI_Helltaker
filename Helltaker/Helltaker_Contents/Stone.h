#pragma once

#include "HitActor.h"

// ���� :
class Stone : public HitActor
{
public:
	// constructor destructor
	Stone();
	~Stone();
	
	// delete Function
	Stone(const Stone& _Other) = delete;
	Stone(Stone&& _Other) noexcept = delete;
	Stone& operator=(const Stone& _Other) = delete;
	Stone& operator=(Stone&& _Other) noexcept = delete;

	void IdleStart();
	void Idle(float _DeltaTime);
	void HitStart(EMoveActorDir _OtherMoveDir);
	void Hit(float _DeltaTime);
	void HitMoveEnd(float _DeltaTime);

	void SetStoneType(int _Type);

protected:
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(int _X, int _Y) override;

	void StateChange(EHitActorState _State, EMoveActorDir _OtherMoveDir = EMoveActorDir::None) override;
	void StateUpdate(float _DeltaTime) override;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const FVector StoneScale = { 0.9f, 0.9f };

	static bool IsLoad;
};

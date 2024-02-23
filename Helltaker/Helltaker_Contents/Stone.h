#pragma once

#include "HitActor.h"

// Ό³Έν :
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

	void Idle(float _DeltaTime);
	void IdleStart();
	void Hit(float _DeltaTime);
	void HitStart();
	void Move(float _DeltaTime);
	void MoveStart() override;

	void SetStoneImg(std::string_view _Name);

protected:
	void NextStateCheck(EMoveActorDir _OtherMoveDir) override;
	void NextTileCheck(Point _Point);

	void StateChange(EHitActorState _State);
	void StateUpdate(float _DeltaTime);
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

	const FVector StoneScale = { 0.825f, 0.85f };

	static bool IsLoad;
};


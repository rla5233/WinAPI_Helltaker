#pragma once

#include "SinMoveActor.h"

// Ό³Έν :
class Sin_Thorn : public SinMoveActor
{
public:
	// constructor destructor
	Sin_Thorn();
	~Sin_Thorn();
	
	// delete Function
	Sin_Thorn(const Sin_Thorn& _Other) = delete;
	Sin_Thorn(Sin_Thorn&& _Other) noexcept = delete;
	Sin_Thorn& operator=(const Sin_Thorn& _Other) = delete;
	Sin_Thorn& operator=(Sin_Thorn&& _Other) noexcept = delete;

	void SetDownPosY(float _PosY)
	{
		DownPosY = _PosY;
	}
	
	void SetUpPosY(float _PosY)
	{
		UpPosY = _PosY;
	}

	static const FVector& GetThornScale()
	{
		return ThornScale;
	}

	EThornState GetState()
	{
		return State;
	}

	void SetState(EThornState _State)
	{
		State = _State;
	}

	void StateChange(EThornState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
	void HeroHitCheck();

	void UpStart();
	void Up(float _DeltaTime);

	void DownStart();
	void Down(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::vector<UImageRenderer*> ImageRenderer;
	static const FVector ThornScale;
	static const float ChangeInter;

	float DownPosY = 0.0f;
	float UpPosY = 0.0f;

	EThornState State = EThornState::None;
	static const int ThornCount;
};


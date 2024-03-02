#pragma once

#include "SinComponent.h"

// Ό³Έν :
class Sin_Thorn : public SinComponent
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

	static const FVector& GetThornScale()
	{
		return ThornScale;
	}

	void StateChange(EThornState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart();
	void Idle(float _DeltaTime);

	void UpStart();
	void Up(float _DeltaTime);

	void DownStart();
	void Down(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	static const FVector ThornScale;
	static const float ChangeInter;

	EThornState State = EThornState::None;
	static bool IsLoad;
};


#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Gear : public RenderActor
{
public:
	// constructor destructor
	Gear();
	~Gear();
	
	// delete Function
	Gear(const Gear& _Other) = delete;
	Gear(Gear&& _Other) noexcept = delete;
	Gear& operator=(const Gear& _Other) = delete;
	Gear& operator=(Gear&& _Other) noexcept = delete;

	void StateChange(ESinGearState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void WorkingStart();
	void Working(float _DeltaTime);
	void Working1();

	void StopStart();
	void Stop(float _DeltaTime);
	void Stop1();
	void Stop2();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* L_ImageRenderer = nullptr;
	UImageRenderer* R_ImageRenderer = nullptr;
	static const FVector Scale;
	static const float WorkingInter;
	int WorkOrder = -1;
	int StopOrder = -1;

	ESinGearState State = ESinGearState::None;
	static bool IsLoad;
};


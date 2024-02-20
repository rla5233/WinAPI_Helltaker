#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Thorn : public RenderActor
{
public:
	// constructor destructor
	Thorn();
	~Thorn();

	// delete Function
	Thorn(const Thorn& _Other) = delete;
	Thorn(Thorn&& _Other) noexcept = delete;
	Thorn& operator=(const Thorn& _Other) = delete;
	Thorn& operator=(Thorn&& _Other) noexcept = delete;

	EThornState GetState() const
	{
		return State;
	}

	void SetPoint(Point _Point)
	{
		ThornPoint = _Point;
	}

	void StateChange(EThornState _State);
private:
	void Idle(float _DeltaTime);
	void IdleStart();
	void Up(float _DeltaTime);
	void UpStart();
	void Down(float _DeltaTime);
	void DownStart();

protected:
	void StateUpdate(float _DeltaTime);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	Point ThornPoint = { -1, -1 };
	EThornState State = EThornState::None;

	static const FVector IdleScale;
	static const float ChangeInter;
	static bool IsLoad;
};

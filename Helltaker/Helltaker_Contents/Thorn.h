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

	void Idle(float _DeltaTime);
	void IdleStart();
	void Up(float _DeltaTime);
	void UpStart();
	void Down(float _DeltaTime);
	void DownStart();

	void SetPoint(Point _Point)
	{
		ThornPoint.X = _Point.X;
		ThornPoint.Y = _Point.Y;
	}

	EThornState GetState() const
	{
		return State;
	}

	void StateChange(EThornState _State);
protected:
	void StateUpdate(float _DeltaTime);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float UpDownInter = 0.05f;

	Point ThornPoint = { -1, -1 };
	EThornState State = EThornState::None;
	static bool IsLoad;
};

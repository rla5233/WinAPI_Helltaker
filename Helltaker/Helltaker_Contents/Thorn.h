#pragma once

#include "RenderActor.h"
#include "ContentsHelper.h"

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

	void SetPoint(int _X, int _Y)
	{
		Point_X = _X;
		Point_Y = _Y;
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
	UImageRenderer* Renderer = nullptr;

	const FVector IdleScale = { 0.9f, 0.9f };
	const float UpDownInter = 0.05f;

	int Point_X = -1;
	int Point_Y = -1;
	EThornState State = EThornState::None;
	static bool IsLoad;
};

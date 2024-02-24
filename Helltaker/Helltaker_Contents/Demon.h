#pragma once

#include "RenderActor.h"

// ���� :
class Demon : public RenderActor
{
public:
	// constructor destructor
	Demon();
	~Demon();
	
	// delete Function
	Demon(const Demon& _Other) = delete;
	Demon(Demon&& _Other) noexcept = delete;
	Demon& operator=(const Demon& _Other) = delete;
	Demon& operator=(Demon&& _Other) noexcept = delete;

	void IdleStart();
	void Idle(float _DeltaTime);

	void VictoryStart();

	void StateChange(EDemonState _State);
	void StateUpdate(float _DeltaTime);

	void SetDemon(std::string_view _Name);
	void LoveSignAnimation(float _DeltaTime);

	void SetLocationPoint(Point _Point)
	{
		LocationPoint = _Point;
	}

	Point GetLocationPoint() const
	{
		return LocationPoint;
	}

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	UImageRenderer* LoveSignRenderer = nullptr;
	const FVector LoveSignScale = { 0.3f, 0.4f };
	float LoveSignMove = 0.0f;
	float LoveSignSpeed = 0.0f;
	static const float LoveSignY_Location;
	static const float LoveSignY_MaxLocation;
	bool IsUp = true;

	static const FVector IdleScale;
	static const float IdleInter;
	
	Point LocationPoint = { -1, -1 };
	EDemonState State = EDemonState::None;
	static bool IsLoad;
};


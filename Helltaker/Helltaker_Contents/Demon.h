#pragma once

#include "RenderActor.h"

class StarEffect
{
public:
	UImageRenderer* EffectRenderer = nullptr;
	bool IsMove = false;
};

// Ό³Έν :
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

	void StateChange(EDemonState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void VictoryStart();
	void Victory(float _DeltaTime);

	void CreateStarEffect();
	void StarMove();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	std::list<StarEffect*> AllStarEffect;
	static const int StarEffectCount;
	int EffectCount = 0;

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


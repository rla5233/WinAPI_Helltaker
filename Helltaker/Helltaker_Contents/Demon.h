#pragma once

#include "RenderActor.h"

class StarEffect;

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

	void SetDemon(std::string_view _Name, const FTransform& _FTransform);
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

	void StarEffectUpdate(float _DeltaTime);
	void CreateStarEffect();
	void StarEffectMoveUpdate(float _DeltaTime);

	void LovePlosionUpdate();
	void CreateLovePlosion(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	static const FVector IdleScale;
	static const float IdleInter;

	UImageRenderer* LoveSignRenderer = nullptr;
	const FVector LoveSignScale = { 0.3f, 0.4f };
	float LoveSignMove = 0.0f;
	float LoveSignSpeed = 0.0f;
	static const float LoveSignY_Location;
	static const float LoveSignY_MaxLocation;
	bool IsUp = true;

	int VictoryOrder = -1;
	int EffectCount = 0;
	float DelayTimeCount = 0.0f;
	std::list<StarEffect> AllStarEffect;
	static const int StarEffectCount;

	UImageRenderer* LovePlosionRenderer = nullptr;
	static const FVector LovePlosionScale;
	static const float LovePlosionInter;
	static const float LovePlosionDelay;

	
	Point LocationPoint = { -1, -1 };
	EDemonState State = EDemonState::None;
	static bool IsLoad;
};

class StarEffect
{
	friend Demon;
public:
	void StarEffectMove(const Demon* const _Demon, float _DeltaTime, float _TimeWeight = 0.0f);

private:
	UImageRenderer* EffectRenderer = nullptr;
	FVector StartPos = FVector::Zero;
	static FVector TargetPos;
	float MoveTime = 0.0f;
	bool IsMove = false;
};
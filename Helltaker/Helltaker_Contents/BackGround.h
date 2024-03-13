#pragma once

#include "RenderActor.h"

// Ό³Έν :
class BackGround : public RenderActor
{
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void CreateImageRenderer(SinRenderOrder _Order);

	void CreateBackGround(std::string_view _Name, EBackGroundType _Type = EBackGroundType::Default);
	void CreateSceneBackGround(std::string_view _Name);
	void BackGroundChange(std::string_view _Name);

	void SetStartScale(const FVector& _StartScale)
	{
		StartScale = _StartScale;
	}

	void SetTargetScale(const FVector& _TargetScale)
	{
		TargetScale = _TargetScale;
	}

	void ScaleChangeOn()
	{
		IsScaleChange = true;
	}

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	void StateChange(EBGState _State);

protected:
	void Tick(float _DeltaTime) override;

private:
	void ScaleChangeStart();
	void ScaleChange(float _DeltaTime);

	void ScaleChangeUpdate(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	void MoveUpdate(float _DeltaTime);

	void MoveOut_YStart();
	void MoveOut_Y();

	void ScaleZeroY_Start();
	void ScaleZeroY();

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;

	FVector StartScale = FVector::Zero;
	FVector TargetScale = FVector::Zero;
	float ScaleChangeTime = 0.0f;
	bool IsScaleChange = false;

	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	bool IsMove = false;

	EBGState State = EBGState::None;
};

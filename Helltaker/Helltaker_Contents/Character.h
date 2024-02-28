#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Character : public RenderActor
{
public:
	// constructor destructor
	Character();
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	void CreateImageRenderer(RenderOrder _Order);
	void CreateNameRenderer(RenderOrder _Order);

	void ImageRendererMoveUpdate(float _DeltaTime, float _TimeWeight = 1.0f);

	void ImageRendererMoveOn(const FVector& _StartPos, const FVector& _TargetPos)
	{
		StartPos = _StartPos;
		TargetPos = _TargetPos;
		IsImageMoveValue = true;
	}

	bool GetIsImageRendererMoveValue() const
	{
		return IsImageMoveValue;
	}

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	UImageRenderer* GetNameRenderer() const
	{
		return NameRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* NameRenderer = nullptr;

	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	bool IsImageMoveValue = false;
};

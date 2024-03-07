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

	void ScaleChangeUpdate(const FVector& _TargetScale, float _DeltaTime, float _TimeWeight = 1.0f);
	void ScaleChangeOn()
	{
		StartScale = ImageRenderer->GetTransform().GetScale();
		IsScaleChange = true;
	}

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;

	FVector StartScale = FVector::Zero;
	float ScaleChangeTime = 0.0f;
	bool IsScaleChange = false;
};

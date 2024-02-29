#pragma once
#include "ContentsHelper.h"

#include <EngineBase/Transform.h>
#include <EngineCore/Actor.h>

class ChapterManager;

// Ό³Έν :
class RenderActor : public AActor
{
public:
	// constructor destructor
	RenderActor();
	~RenderActor();
	
	// delete Function
	RenderActor(const RenderActor& _Other) = delete;
	RenderActor(RenderActor&& _Other) noexcept = delete;
	RenderActor& operator=(const RenderActor& _Other) = delete;
	RenderActor& operator=(RenderActor&& _Other) noexcept = delete;

	ChapterManager* GetChapter();

	UImageRenderer* CreateImageRenderer(RenderOrder _Order);
	UImageRenderer* CreateImageRenderer(SinRenderOrder _Order);
	
	bool FadeInUpdate(UImageRenderer* const _Renderer, float _DeltaTime, float _TimeWeight = 1.0f);
	void FadeInOn()
	{
		IsFadeIn = true;
	}

	bool FadeOutUpdate(UImageRenderer* const _Renderer, float _DeltaTime, float _TimeWeight = 1.0f);
	void FadeOutOn()
	{
		IsFadeOut = true;
	}

	void VibrationEffect(UImageRenderer* _Renderer);

protected:
	
private:
	bool IsFadeIn = false;
	bool IsFadeOut = false;

	float TimeCount = 0.0f;
};


#pragma once
#include "ContentsHelper.h"

#include <EngineBase/Transform.h>
#include <EngineCore/Actor.h>

class ChapterManager;
class SinChapterManager;
class SinCutSceneManager;

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
	SinChapterManager* GetSinChapter();
	SinCutSceneManager* GetSinCutSceneChapter();
	
	
	void FadeInUpdate(
		UImageRenderer* const _Renderer,
		float _DeltaTime, 
		float _TimeWeight = 1.0f,
		float _Start = 0.0f, 
		float _End = 1.0f);

	void FadeInOn()
	{
		IsFadeIn = true;
	}

	bool IsFadeInOn() const
	{
		return IsFadeIn;
	}

	void FadeOutUpdate(
		UImageRenderer* const _Renderer,
		float _DeltaTime,
		float _TimeWeight = 1.0f,
		float _Start = 1.0f,
		float _End = 0.0f);

	void FadeOutOn()
	{
		IsFadeOut = true;
	}

	bool IsFadeOutOn() const
	{
		return IsFadeOut;
	}

	void ImgMoveUpdate(
		UImageRenderer* const _Renderer,
		const FVector& _StartPos,
		const FVector& _TargetPos,
		float _DeltaTime,
		float _TimeWeight = 1.0f
	);

	void ImgMoveUpdate(
		const std::vector<UImageRenderer*>& _Renderer,
		const std::vector<FVector>& _StartPos,
		const std::vector<FVector>& _TargetPos,
		float _DeltaTime,
		float _TimeWeight = 1.0f
	);

	void ImgMoveOn()
	{
		IsImgMove = true;
	}

	bool IsImgMoveOn() const
	{
		return IsImgMove;
	}

protected:
	void BeginPlay() override;
	
private:
	bool IsFadeIn = false;
	bool IsFadeOut = false;
	bool IsImgMove = false;

	float FadeTimeCount = 0.0f;
	float MoveTimeCount = 0.0f;

	static bool IsLoad;
};


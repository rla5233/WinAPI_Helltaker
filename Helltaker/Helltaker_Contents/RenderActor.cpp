#include "RenderActor.h"

#include "ChapterManager.h"
#include "SinChapterManager.h"

RenderActor::RenderActor()
{
}

RenderActor::~RenderActor()
{
}

UImageRenderer* RenderActor::CreateImageRenderer(RenderOrder _Order)
{
	return AActor::CreateImageRenderer(static_cast<int>(_Order));
}

UImageRenderer* RenderActor::CreateImageRenderer(SinRenderOrder _Order)
{
	return AActor::CreateImageRenderer(static_cast<int>(_Order));
}

ChapterManager* RenderActor::GetChapter()
{
	ChapterManager* Ptr = dynamic_cast<ChapterManager*>(GetWorld());
	if (nullptr == Ptr)
	{
		MsgBoxAssert("Chapter is nullptr");
	}

	return Ptr;
}

SinChapterManager* RenderActor::GetSinChapter()
{
	SinChapterManager* Ptr = dynamic_cast<SinChapterManager*>(GetWorld());
	if (nullptr == Ptr)
	{
		MsgBoxAssert("Chapter is nullptr");
	}

	return Ptr;
}

bool RenderActor::FadeInUpdate(
	UImageRenderer* const _Renderer, 
	float _DeltaTime,
	float _TimeWeight /* = 1.0f*/,
	float _Start /* = 0.0f */,
	float _End /* = 1.0f */)
{
	if (true == IsFadeIn)
	{
		TimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(_Start, _End, TimeCount);
		_Renderer->SetAlpha(NextAlpha);

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsFadeIn = false;
		}
	}

	return IsFadeIn;
}

bool RenderActor::FadeOutUpdate(
	UImageRenderer* const _Renderer, 
	float _DeltaTime, 
	float _TimeWeight /* = 1.0f*/,
	float _Start/* = 1.0f */,
	float _End /* = 0.0f */)
{
	if (true == IsFadeOut)
	{
		TimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(_Start, _End, TimeCount);
		_Renderer->SetAlpha(NextAlpha);

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsFadeOut = false;
		}
	}

	return IsFadeOut;
}

void RenderActor::VibrationEffect(UImageRenderer* _Renderer)
{
	FTransform OrgTransform = _Renderer->GetTransform();


	_Renderer->SetTransform(OrgTransform);
}
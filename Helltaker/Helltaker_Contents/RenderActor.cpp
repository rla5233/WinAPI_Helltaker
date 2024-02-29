#include "RenderActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

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

ChapterManager* RenderActor::GetChapter()
{
	ChapterManager* Ptr = dynamic_cast<ChapterManager*>(GetWorld());
	if (nullptr == Ptr)
	{
		MsgBoxAssert("Chapter is nullptr");
	}

	return Ptr;
}

bool RenderActor::FadeInUpdate(UImageRenderer* const _Renderer, float _DeltaTime, float _TimeWeight /* = 1.0f*/)
{
	if (true == IsFadeIn)
	{
		TimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(0, 1, TimeCount);
		_Renderer->SetAlpha(NextAlpha);

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsFadeIn = false;
		}
	}

	return IsFadeIn;
}

bool RenderActor::FadeOutUpdate(UImageRenderer* const _Renderer, float _DeltaTime, float _TimeWeight)
{
	if (true == IsFadeOut)
	{
		TimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(1, 0, TimeCount);
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
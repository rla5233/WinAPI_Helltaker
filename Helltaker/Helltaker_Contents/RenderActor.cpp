#include "RenderActor.h"

#include "ChapterManager.h"
#include "SinChapterManager.h"
#include "SinCutSceneManager.h"

bool RenderActor::IsLoad = false; 

RenderActor::RenderActor()
{
}

RenderActor::~RenderActor()
{
}

void RenderActor::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

		IsLoad = true;
	}
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

SinCutSceneManager* RenderActor::GetSinCutSceneChapter()
{
	SinCutSceneManager* Ptr = dynamic_cast<SinCutSceneManager*>(GetWorld());
	if (nullptr == Ptr)
	{
		MsgBoxAssert("Chapter is nullptr");
	}

	return Ptr;
}

void RenderActor::FadeInUpdate(
	UImageRenderer* const _Renderer, 
	float _DeltaTime,
	float _TimeWeight /* = 1.0f*/,
	float _Start /* = 0.0f */,
	float _End /* = 1.0f */)
{
	if (true == IsFadeIn)
	{
		FadeTimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(_Start, _End, FadeTimeCount);
		_Renderer->SetAlpha(NextAlpha);

		if (1.0f <= FadeTimeCount)
		{
			FadeTimeCount = 0.0f;
			IsFadeIn = false;
		}
	}
}

void RenderActor::FadeOutUpdate(
	UImageRenderer* const _Renderer, 
	float _DeltaTime, 
	float _TimeWeight /* = 1.0f*/,
	float _Start/* = 1.0f */,
	float _End /* = 0.0f */)
{
	if (true == IsFadeOut)
	{
		FadeTimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(_Start, _End, FadeTimeCount);
		_Renderer->SetAlpha(NextAlpha);

		if (1.0f <= FadeTimeCount)
		{
			FadeTimeCount = 0.0f;
			IsFadeOut = false;
		}
	}
}

void RenderActor::ImgMoveUpdate(
	UImageRenderer* const _Renderer, 
	const FVector& _StartPos, 
	const FVector& _TargetPos, 
	float _DeltaTime, 
	float _TimeWeight /* = 1.0f */)
{
	if (true == IsImgMove)
	{
		MoveTimeCount += _DeltaTime * _TimeWeight;
		FVector NextPos = FVector::LerpClamp(_StartPos, _TargetPos, MoveTimeCount);
		_Renderer->SetPosition(NextPos);

		if (1.0f <= MoveTimeCount)
		{
			MoveTimeCount = 0.0f;
			IsImgMove = false;
		}
	}
}

void RenderActor::ImgMoveUpdate(
	const std::vector<UImageRenderer*>& _Renderer, 
	const std::vector<FVector>& _StartPos, 
	const std::vector<FVector>& _TargetPos, 
	float _DeltaTime, 
	float _TimeWeight /* = 1.0f */)
{
	if (true == IsImgMove)
	{
		MoveTimeCount += _DeltaTime * _TimeWeight;
		
		for (size_t i = 0; i < _Renderer.size(); i++)
		{
			FVector NextPos = FVector::LerpClamp(_StartPos[i], _TargetPos[i], MoveTimeCount);
			_Renderer[i]->SetPosition(NextPos);
		}

		if (1.0f <= MoveTimeCount)
		{
			MoveTimeCount = 0.0f;
			IsImgMove = false;
		}
	}
}

void RenderActor::ScaleUp_Update(
	UImageRenderer* const _Renderer, 
	const FVector& _StartScale, 
	const FVector& _TargetScale, 
	float _DeltaTime, 
	float _TimeWeight)
{
	if (true == IsScaleUp)
	{
		ScaleUpTimeCount += _DeltaTime * _TimeWeight;

		FVector NextScale = FVector::LerpClamp(_StartScale, _TargetScale, ScaleUpTimeCount);
		_Renderer->SetScale(NextScale);

		if (1.0f <= ScaleUpTimeCount)
		{
			ScaleUpTimeCount = 0.0f;
			IsScaleUp = false;
		}
	}
}

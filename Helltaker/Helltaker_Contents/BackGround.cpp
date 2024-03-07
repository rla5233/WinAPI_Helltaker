#include "BackGround.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::CreateImageRenderer(SinRenderOrder _Order)
{
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void BackGround::CreateBackGround(std::string_view _Name, EBackGroundType _Type)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.Half2D()});
	SetName(_Name);

	switch (_Type)
	{
	case EBackGroundType::Default:
		ImageRenderer = RenderActor::CreateImageRenderer(RenderOrder::BackGround);
		break;
	case EBackGroundType::Sin:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::BackGround);
		break;
	}
	ImageRenderer->SetImage(GetName() + ".png");
	
	FVector ImgScale = ImageRenderer->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * (ImgScale.Y / 1080) };
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void BackGround::CreateSceneBackGround(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.Half2D() });
	SetName(_Name);
	ImageRenderer = RenderActor::CreateImageRenderer(RenderOrder::SceneBackGround);
	ImageRenderer->SetImage(GetName() + ".png");

	FVector ImgScale = ImageRenderer->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * (ImgScale.Y / 1080) };
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void BackGround::BackGroundChange(std::string_view _Name)
{
	ImageRenderer->SetImage(_Name);
}

void BackGround::ScaleChangeUpdate(const FVector& _TargetScale, float _DeltaTime, float _TimeWeight)
{
	if (true == IsScaleChange)
	{
		ScaleChangeTime += (_DeltaTime * _TimeWeight);
		
		FVector NextScale = FVector::LerpClamp(StartScale, _TargetScale, ScaleChangeTime);
		ImageRenderer->SetScale(NextScale);

		if (1.0f <= ScaleChangeTime)
		{
			ScaleChangeTime = 0.0f;
			IsScaleChange = false;
		}
	}
}
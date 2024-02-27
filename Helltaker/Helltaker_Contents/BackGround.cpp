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

void BackGround::CreateBackGround(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.Half2D()});
	SetName(_Name);
	ImageRenderer = CreateImageRenderer(RenderOrder::BackGround);
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
	ImageRenderer = CreateImageRenderer(RenderOrder::SceneBackGround);
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
#include "BackGround.h"

#include "ContentsHelper.h"

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
	ImageRenderer->SetTransform({ {0, 0}, WinScale });
}

void BackGround::BackGroundChange(std::string_view _Name)
{
	ImageRenderer->SetImage(_Name);
}

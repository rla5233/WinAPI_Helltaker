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
	Renderer = CreateImageRenderer(RenderOrder::BackGround);
	Renderer->SetImage(GetName() + ".png");
	Renderer->SetTransform({ {0, 0}, WinScale });
}

void BackGround::BackGroundChange(std::string_view _Name)
{
	Renderer->SetImage(_Name);
}

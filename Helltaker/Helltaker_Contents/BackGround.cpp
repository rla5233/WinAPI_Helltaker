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
	LoadImg("BackGround");
	CreateImageRenderer(RenderOrder::BackGround);
	SetImg(GetName() + ".png");
	SetTransform({ {0, 0}, WinScale });
}

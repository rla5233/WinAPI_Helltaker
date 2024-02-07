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
	SetActorLocation({ WinScale.X / 2.0f, WinScale.Y / 2.0f });
	SetName(_Name);
	LoadImg("BackGround");
	CreateImageRenderer(RenderOrder::BackGround);
	SetImg(GetName());
	SetTransform({ {0, 0}, WinScale });
}

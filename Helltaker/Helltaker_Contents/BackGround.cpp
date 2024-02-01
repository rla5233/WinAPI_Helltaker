#include "BackGround.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::LoadRenderImage(std::string_view _Name)
{
	RenderActor::LoadRenderImage(_Name);

	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Stage\\BackGround");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.GetFullPath() + "\\" + _Name.data());
}

void BackGround::SetRenderImage(std::string_view _Name)
{
	RenderActor::SetRenderImage(_Name);

	Renderer = CreateImageRenderer(0);
	Renderer->SetImage(_Name);
	Renderer->SetTransform({ {0, 0}, {1280, 720} });
	Renderer->SetImageCuttingTransform({ {0, 0}, {1920, 1080} });
}

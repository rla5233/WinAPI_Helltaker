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

void BackGround::LoadRenderImage(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\BackGround\\");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.GetFullPath() + _Path.data() + "\\" + _Name.data());
}

void BackGround::SetRenderImage(std::string_view _Name, RenderOrder _Order)
{
	SetRenderImage(_Name, static_cast<int>(_Order));
}

void BackGround::SetRenderImage(std::string_view _Name, int _Order)
{
	FVector Scale = ContentsHelper::GetWindowScale();

	Renderer = CreateImageRenderer(_Order);
	Renderer->SetImage(_Name);
	Renderer->SetTransform({ {0, 0}, Scale });
	Renderer->SetImageCuttingTransform({ {0, 0}, Renderer->GetImage()->GetScale() });
}

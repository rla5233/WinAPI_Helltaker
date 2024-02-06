#include "BackGround.h"

#include "ContentsHelper.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::LoadBG()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\BackGround");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()));
}

void BackGround::SetBG()
{
	Renderer = CreateImageRenderer(static_cast<int>(RenderOrder::BackGround));
	Renderer->SetImage(GetName());
	Renderer->SetTransform({ {0,0}, ContentsHelper::GetWindowScale() });
}

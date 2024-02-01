#include "BackGround.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::LoadStageBackGround(std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Stage\\BackGround");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.GetFullPath() + _Name.data());
}

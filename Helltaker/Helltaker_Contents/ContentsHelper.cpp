#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

FVector ContentsHelper::GetWindowScale()
{
    return GEngine->MainWindow.GetWindowScale();
}

float ContentsHelper::GetOneTileWidth()
{
    return GEngine->MainWindow.GetWindowScale().X / 19;
}

void ContentsHelper::LoadImg(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(_Name));
}



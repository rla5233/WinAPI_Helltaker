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

FVector ContentsHelper::GetTileScale()
{
	FVector WinScale = GetWindowScale();
	FVector TileScale = { WinScale.X / 19.2f, WinScale.Y / 10.8f};
	return TileScale;
}

void ContentsHelper::LoadImg(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(_Name));
}

void ContentsHelper::LoadFolder(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath(_Name));
}



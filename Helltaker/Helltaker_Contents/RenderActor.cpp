#include "RenderActor.h"

#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

RenderActor::RenderActor()
{
}

RenderActor::~RenderActor()
{
}

void RenderActor::LoadFolder(std::string_view _Path)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath(GetName()));
}

void RenderActor::LoadImg(std::string_view _Path)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()) + ".png");
}

void RenderActor::LoadImg(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(_Name));
}

UImageRenderer* RenderActor::CreateImageRenderer(RenderOrder _Order)
{
	return AActor::CreateImageRenderer(static_cast<int>(_Order));
}
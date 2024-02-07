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
	ResourcesPath.AppendPath(_Path);
	ResourcesPath.AppendPath(GetName());
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.GetFullPath());
}

void RenderActor::LoadImg(std::string_view _Path)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()));
}

void RenderActor::SetImg(std::string_view _Name)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->SetImage(_Name);
}

void RenderActor::SetTransform(const FTransform& _Value)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->SetTransform(_Value);
}

void RenderActor::CreateImageRenderer(RenderOrder _Order)
{
	Renderer = AActor::CreateImageRenderer(static_cast<int>(_Order));
}

void RenderActor::CreateImageRenderer(int _Order)
{
	Renderer = AActor::CreateImageRenderer(_Order);
}

FVector RenderActor::GetRendererImageScale()
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	return Renderer->GetImage()->GetScale();
}

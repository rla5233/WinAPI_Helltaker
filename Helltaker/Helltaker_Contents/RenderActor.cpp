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

void RenderActor::CreateAnimation(std::string_view _AnimationName, std::string_view _ImageName, int _Start, int _End, float _Inter, bool _Loop)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->CreateAnimation(_AnimationName, _ImageName, _Start, _End, _Inter, _Loop);
}

void RenderActor::ChangeAnimation(std::string_view _AnimationName)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->ChangeAnimation(_AnimationName);
}

void RenderActor::RenderActiveOn()
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->ActiveOn();
}

void RenderActor::RenderActiveOff()
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("Renderer is nullptr.");
	}

	Renderer->ActiveOff();
}
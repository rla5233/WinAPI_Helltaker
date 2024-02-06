#include "Dialogue.h"

#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Dialogue::Dialogue()
{
}

Dialogue::~Dialogue()
{
}

void Dialogue::LoadFolder()
{

}

void Dialogue::LoadImg()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Secene\\Dialogue");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()));
}

void Dialogue::SetImg(bool _SetOrgScale)
{
	Renderer = CreateImageRenderer(static_cast<int>(RenderOrder::Dialogue));
	Renderer->SetImage(GetName());

	if (true == _SetOrgScale)
	{
		// 수정필요
		Scale = Renderer->GetImage()->GetScale();
		Scale.Y /= 1.5f;
	}

	Renderer->SetTransform({ {0,0}, Scale });
}

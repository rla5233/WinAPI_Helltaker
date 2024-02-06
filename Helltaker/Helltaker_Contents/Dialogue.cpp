#include "Dialogue.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Dialogue::Dialogue()
{
}

Dialogue::~Dialogue()
{
}

void Dialogue::LoadFolderDialogue()
{

}

void Dialogue::SetFolderDialogue()
{

}

void Dialogue::LoadImgDialogue()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Dialogue");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()));
}

void Dialogue::SetImgDialogue(bool _SetOrgScale)
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

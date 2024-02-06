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

void Dialogue::SetImgDialogue()
{
	Renderer = CreateImageRenderer(static_cast<int>(RenderOrder::Dialogue));
	Renderer->SetImage(GetName());
	Renderer->SetTransform({ {0,0}, Scale });
}

#include "Character.h"

#include "ContentsEnum.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Character::Character()
{
}

Character::~Character()
{
}

void Character::LoadFolder()
{}

void Character::SetFolder()
{}

void Character::LoadImg()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Secene\\Characters");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(GetName()));
}

void Character::SetImg(bool _SetOrgScale)
{
	Renderer = CreateImageRenderer(static_cast<int>(RenderOrder::Character));
	Renderer->SetImage(GetName());

	if (true == _SetOrgScale)
	{
		// 수정필요
		Scale = Renderer->GetImage()->GetScale();
	}

	Renderer->SetTransform({ {0,0}, Scale });
}

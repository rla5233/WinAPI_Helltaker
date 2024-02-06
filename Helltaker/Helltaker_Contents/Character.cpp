#include "Character.h"

#include "ContentsHelper.h"

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
		// �����ʿ�
		Scale = Renderer->GetImage()->GetScale();
		Scale.X /= 2;
		Scale.Y /= 2;
	}

	Renderer->SetTransform({ {0,0}, Scale });
}

#include "UI.h"

#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

UI::UI()
{
}

UI::~UI()
{
}

void UI::LoadFolder()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\UI");
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath(GetName()));
}

void UI::LoadImg()
{}

void UI::SetImg(bool _SetOrgScale)
{
	Renderer = CreateImageRenderer(static_cast<int>(RenderOrder::UI));
	Renderer->SetImage(GetName());

	if (true == _SetOrgScale)
	{
		// 수정필요
		Scale = Renderer->GetImage()->GetScale();
		Scale.X /= 2;
		Scale.Y /= 2;
	}

	Renderer->SetTransform({ {0, 0}, Scale });
}

void UI::CreateUIAnimation(std::string_view _AnimationName, std::string_view _ImageName, int _Start, int _End, float _Inter, bool _Loop)
{
	Renderer->CreateAnimation(_AnimationName, _ImageName, _Start, _End, _Inter, _Loop);
}

void UI::ChangeUIAnimation(std::string_view _AnimationName)
{
	Renderer->ChangeAnimation(_AnimationName);
}

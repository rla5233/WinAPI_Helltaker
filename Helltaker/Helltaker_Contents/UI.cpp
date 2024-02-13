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

void UI::CreateImageRenderer(RenderOrder _Order)
{
	Renderer = RenderActor::CreateImageRenderer(_Order);
}

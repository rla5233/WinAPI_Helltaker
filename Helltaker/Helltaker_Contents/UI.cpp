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
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void UI::CreateTextRenderer(RenderOrder _Order)
{
	TextRenderer = RenderActor::CreateImageRenderer(_Order);
}

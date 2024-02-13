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

void Dialogue::CreateImageRenderer(RenderOrder _Order)
{
	Renderer = RenderActor::CreateImageRenderer(_Order);
}

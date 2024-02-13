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

void Character::CreateImageRenderer(RenderOrder _Order)
{
	Renderer = RenderActor::CreateImageRenderer(_Order);
}

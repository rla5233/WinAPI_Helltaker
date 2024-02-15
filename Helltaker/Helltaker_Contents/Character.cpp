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
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void Character::CreateNameRenderer(RenderOrder _Order)
{
	NameRenderer = RenderActor::CreateImageRenderer(_Order);
}

#include "Monster.h"
#include <EngineCore/EngineCore.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::BeginPlay()
{
	MonsterRenderer = CreateImageRenderer(1);
	MonsterRenderer->SetPosition({ 200, 200 });
	MonsterRenderer->SetScale({ 30, 30 });
}

void Monster::Tick(float _DeltaTime)
{	
}

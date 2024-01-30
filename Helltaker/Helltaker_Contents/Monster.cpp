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
	MonsterRenderer->SetPosition({ 500, 500 });
	MonsterRenderer->SetScale({ 50, 50 });
}

void Monster::Tick(float _DeltaTime)
{	
}

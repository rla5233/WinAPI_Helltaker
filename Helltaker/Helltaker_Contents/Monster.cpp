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
	MonsterRenderer = CreateImageRenderer(0);
	MonsterRenderer->SetImageToScale("Monster.png");
	//MonsterRenderer->SetScale({ 50, 50 });
}

void Monster::Tick(float _DeltaTime)
{	
}

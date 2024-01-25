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
	SetActorLocation({ 200, 200 });
	SetActorScale({ 45, 45 });
}

void Monster::Tick(float _DeltaTime)
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

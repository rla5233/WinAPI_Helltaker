#include "Hero.h"

#include <EngineCore/EngineCore.h>


Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::BeginPlay()
{
	MoveActor::BeginPlay();

	HeroRenderer = CreateImageRenderer(0);
	HeroRenderer->SetImageToScale("Hero0022.bmp");
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}
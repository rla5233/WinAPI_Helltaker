#include "Skeleton.h"

#include <EngineCore/EngineCore.h>



Skeleton::Skeleton()
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	MoveActor::BeginPlay();

	CreateImageRenderer(2);

	//SkeletonRenderer->SetImageToScale("Skeleton.bmp");
	//SkeletonRenderer->SetScale({ 50, 50 });
}

void Skeleton::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);
}

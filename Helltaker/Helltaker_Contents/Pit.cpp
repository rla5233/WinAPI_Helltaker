#include "Pit.h"

bool Pit::IsLoad = false;

const FVector Pit::SinPitScale = { 0.283f, 0.6074f };
const float Pit::SinPitSpeedY = -50.0f;

Pit::Pit()
{
}

Pit::~Pit()
{
}

void Pit::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{


		IsLoad = true;
	}
}

void Pit::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);


}

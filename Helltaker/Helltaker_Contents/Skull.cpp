#include "Skull.h"

bool Skull::IsLoad = false;

Skull::Skull()
{
}

Skull::~Skull()
{
}

void Skull::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BSkull.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TSkull.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LArm.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RArm.png");

		IsLoad = true;
	}

}

void Skull::IdleStart()
{
}

void Skull::Idle(float _DeltaTime)
{
}

void Skull::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);
}

void Skull::StateUpdate(float _DeltaTime)
{
}

void Skull::StateChange(ESinSkullState _State)
{
}
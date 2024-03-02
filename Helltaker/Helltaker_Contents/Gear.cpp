#include "Gear.h"

bool Gear::IsLoad = false;

Gear::Gear()
{
}

Gear::~Gear()
{
}

void Gear::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_LGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_RGears_001.png");

		IsLoad = true;
	}
}

void Gear::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Gear::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinGearState::Idle:
		break;
	case ESinGearState::Start:
		break;
	case ESinGearState::Active:
		break;
	case ESinGearState::Stop:
		break;
	}
}

void Gear::StateChange(ESinGearState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinGearState::Idle:
			break;
		case ESinGearState::Start:
			break;
		case ESinGearState::Active:
			break;
		case ESinGearState::Stop:
			break;
		}
	}
	
	State = _State;	
}
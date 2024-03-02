#include "Sin_Thorn.h"

bool Sin_Thorn::IsLoad = false;

Sin_Thorn::Sin_Thorn()
{
}

Sin_Thorn::~Sin_Thorn()
{
}

void Sin_Thorn::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");

		IsLoad = true;
	}
}

void Sin_Thorn::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Thorn::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EThornState::Idle:
		break;
	case EThornState::Up:
		break;
	case EThornState::Down:
		break;
	}

}


void Sin_Thorn::StateChange(EThornState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EThornState::Idle:
			break;
		case EThornState::Up:
			break;
		case EThornState::Down:
			break;
		}
	}

	State = _State;
}

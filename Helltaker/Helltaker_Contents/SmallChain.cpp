#include "SmallChain.h"

SmallChain::SmallChain()
{
}

SmallChain::~SmallChain()
{
}

void SmallChain::BeginPlay()
{}

void SmallChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SmallChain::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSmallChainState::Idle:

		break;
	case ESinSmallChainState::Hit:

		break;
	}
}

void SmallChain::StateChange(ESinSmallChainState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinSmallChainState::Idle:

			break;
		case ESinSmallChainState::Hit:
			
			break;
		}
	}

	State = _State
}
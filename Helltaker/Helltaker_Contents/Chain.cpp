#include "Chain.h"

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::BeginPlay()
{
	SinComponent::BeginPlay();
}

void Chain::IdleStart()
{
}

void Chain::Idle(float _DeltaTime)
{
}

void Chain::MoveStart()
{
}

void Chain::Move(float _DeltaTime)
{
}

void Chain::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Chain::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinChainState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinChainState::Move:
		Move(_DeltaTime);
		break;
	}
}

void Chain::StateChange(ESinChainState _State)
{
	if (State != _State)
	{	
		switch (_State)
		{
		case ESinChainState::Idle:
			IdleStart();
			break;
		case ESinChainState::Move:
			MoveStart();
			break;
		}
	}

	State = _State;
}
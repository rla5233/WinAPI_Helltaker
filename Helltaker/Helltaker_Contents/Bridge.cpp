#include "Bridge.h"

Bridge::Bridge()
{
}

Bridge::~Bridge()
{
}

void Bridge::BeginPlay()
{
}

void Bridge::IdleStart()
{
}

void Bridge::Idle(float _DeltaTime)
{
}

void Bridge::MoveStart()
{
}

void Bridge::Move(float _DeltaTime)
{
}

void Bridge::StopStart()
{
}

void Bridge::Stop(float _DeltaTime)
{
}

void Bridge::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Bridge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinBridgeState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinBridgeState::Move:
		Move(_DeltaTime);
		break;
	case ESinBridgeState::Stop:
		Stop(_DeltaTime);
		break;
	}
}

void Bridge::StateChange(ESinBridgeState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinBridgeState::Idle:
			IdleStart();
			break;
		case ESinBridgeState::Move:
			MoveStart();
			break;
		case ESinBridgeState::Stop:
			StopStart();
			break;
		}
	}

	State = _State;
}
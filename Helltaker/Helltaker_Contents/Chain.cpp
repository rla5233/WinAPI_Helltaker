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
}

void Chain::StateUpdate(float _DeltaTime)
{
}

void Chain::StateChange(ESinChainState _State)
{
}
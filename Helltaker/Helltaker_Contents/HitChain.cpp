#include "HitChain.h"

bool IsLoad = false;

HitChain::HitChain()
{
}

HitChain::~HitChain()
{
}

void HitChain::BeginPlay()
{
	SinMoveActor::BeginPlay();
}

void HitChain::IdleStart()
{}

void HitChain::Idle(float _DeltaTime)
{}

void HitChain::MoveStart()
{}

void HitChain::Move(float _DeltaTime)
{}

void HitChain::HitStart()
{}

void HitChain::Hit(float _DeltaTime)
{}

void HitChain::DeathStart()
{}

void HitChain::Death(float _DeltaTime)
{}

void HitChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);
}

void HitChain::StateUpdate(float _DeltaTime)
{}

void HitChain::StateChange(ESinHitChainState _State)
{}


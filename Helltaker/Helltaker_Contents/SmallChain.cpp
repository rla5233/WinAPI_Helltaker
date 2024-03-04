#include "SmallChain.h"

bool SmallChain::IsLoad = false;

const FVector SmallChain::V_Scale = { 0.052f, 1.527f };
const FVector SmallChain::H_Scale = { 1.527f, 0.052f };

SmallChain::SmallChain()
{
}

SmallChain::~SmallChain()
{
}

void SmallChain::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_VChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_HChain.png");

		IsLoad = true;
	}
}

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

	State = _State;
}

void SmallChain::CreateImageRenderer()
{
	switch (Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::SmallVChain);
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
		break;
	}
}

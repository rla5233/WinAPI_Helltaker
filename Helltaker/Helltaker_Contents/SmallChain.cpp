#include "SmallChain.h"

bool SmallChain::IsLoad = false;

const FVector SmallChain::V_Scale = { 0.025f, 1.0f };
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

void SmallChain::CreateImageRenderer(ESinSmallChainType _Type)
{
	switch (_Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::SmallVChain);
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
		break;
	}

	Type = _Type;
}

void SmallChain::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	switch (Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer->SetImage("Sin_VChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * V_Scale } });
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer->SetImage("Sin_HChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * H_Scale } });
		break;
	}
}

void SmallChain::Idle(float _DeltaTime)
{
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
		Idle(_DeltaTime);
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
			IdleStart();
			break;
		case ESinSmallChainState::Hit:
			
			break;
		}
	}

	State = _State;
}


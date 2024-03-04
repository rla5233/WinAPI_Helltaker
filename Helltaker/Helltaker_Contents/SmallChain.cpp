#include "SmallChain.h"

bool SmallChain::IsLoad = false;

const FVector SmallChain::V_Scale = { 0.025f, 1.0f };
const FVector SmallChain::H_Scale = { 1.0f, 0.052f };
const float SmallChain::SpeedY = -150.0f;

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

	ImageRenderer->SetAlpha(0.5);
	ImageRenderer->ActiveOff();
}

void SmallChain::Idle(float _DeltaTime)
{
}

void SmallChain::MoveStart()
{
	MoveOn();
}

void SmallChain::Move(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
}

void SmallChain::ShowStart()
{
	ImageRenderer->ActiveOn();
	timecount = 1.0f;
}

void SmallChain::Show(float _DeltaTime)
{
	if (0.0f >= timecount)
	{
		StateChange(ESinSmallChainState::Hit);
		return;
	}

	timecount -= _DeltaTime;
}

void SmallChain::HitStart()
{
	ImageRenderer->SetAlpha(1);
	timecount = 1.0f;
}

void SmallChain::Hit(float _DeltaTime)
{
	if (0.0f >= timecount)
	{
		ImageRenderer->ActiveOff();
		return;
	}

	timecount -= _DeltaTime;
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
	case ESinSmallChainState::Move:
		Move(_DeltaTime);
		break;
	case ESinSmallChainState::Show:
		Show(_DeltaTime);
		break;
	case ESinSmallChainState::Hit:
		Hit(_DeltaTime);
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
		case ESinSmallChainState::Move:
			MoveStart();
			break;
		case ESinSmallChainState::Show:
			ShowStart();
			break;
		case ESinSmallChainState::Hit:
			HitStart();
			break;
		}
	}

	State = _State;
}


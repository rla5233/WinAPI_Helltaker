#include "Pit.h"

bool Pit::IsLoad = false;

const FVector Pit::SinPitScale = { 0.283f, 0.6074f };
const float Pit::SinPitSpeedY = -50.0f;

Pit::Pit()
{
}

Pit::~Pit()
{
}

void Pit::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LPit.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RPit.png");

		IsLoad = true;
	}

	L_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::UnderBackGround);
	R_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::UnderBackGround);
}

void Pit::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Pit::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinPitState::Idle:
		break;
	case ESinPitState::Move:
		break;
	case ESinPitState::Stop:
		break;
	}
}

void Pit::StateChange(ESinPitState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinPitState::Idle:
			break;
		case ESinPitState::Move:
			break;
		case ESinPitState::Stop:
			break;
		}
	}
	
	State = _State;
}
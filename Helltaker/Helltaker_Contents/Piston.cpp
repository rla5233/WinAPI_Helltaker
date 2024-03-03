#include "Piston.h"

bool Piston::IsLoad = false;

Piston::Piston()
{
}

Piston::~Piston()
{
}

void Piston::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TPiston.png");

		IsLoad = true;
	}

	LT_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	RT_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);

	LB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	RB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
}

void Piston::IdleStart()
{

}

void Piston::Idle(float _DeltaTime)
{
}

void Piston::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);
	
	StateUpdate(_DeltaTime);
}

void Piston::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinPistonState::Idle:
		Idle(_DeltaTime);
		break;
	}
}

void Piston::StateChange(ESinPistonState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinPistonState::Idle:
			IdleStart();
			break;
		}
	}

	State = _State;
}
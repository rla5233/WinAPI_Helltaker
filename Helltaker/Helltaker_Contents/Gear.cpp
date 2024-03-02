#include "Gear.h"

bool Gear::IsLoad = false;
const FVector Gear::Scale = { 0.208f, 0.278f };

Gear::Gear()
{
}

Gear::~Gear()
{
}

void Gear::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_LGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_RGears_001.png");

		IsLoad = true;
	}

	L_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	R_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
}

void Gear::IdleStart()
{
}

void Gear::Idle(float _DeltaTime)
{
}

void Gear::ActivateStart()
{
}

void Gear::Activate(float _DeltaTime)
{
}

void Gear::WorkingStart()
{
}

void Gear::Working(float _DeltaTime)
{
}

void Gear::StopStart()
{
}

void Gear::Stop(float _DeltaTime)
{
}

void Gear::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Gear::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinGearState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinGearState::Activate:
		Activate(_DeltaTime);
		break;
	case ESinGearState::Working:
		Working(_DeltaTime);
		break;
	case ESinGearState::Stop:
		Stop(_DeltaTime);
		break;
	}
}

void Gear::StateChange(ESinGearState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinGearState::Idle:
			IdleStart();
			break;
		case ESinGearState::Activate:
			ActivateStart();
			break;
		case ESinGearState::Working:
			WorkingStart();
			break;
		case ESinGearState::Stop:
			StopStart();
			break;
		}
	}
	
	State = _State;	
}
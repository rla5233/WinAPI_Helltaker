#include "Piston.h"

bool Piston::IsLoad = false;

const FVector Piston::Scale = { 0.125f, 0.74f };

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
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.41f;

	LT_ImageRenderer->SetImage("Sin_TPiston.png");
	LT_ImageRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * Scale });

	RT_ImageRenderer->SetImage("Sin_TPiston.png");
	RT_ImageRenderer->SetTransform({ { PosX, 0.0f }, WinScale * Scale });

	LB_ImageRenderer->SetImage("Sin_BPiston.png");
	LB_ImageRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * Scale });

	RB_ImageRenderer->SetImage("Sin_BPiston.png");
	RB_ImageRenderer->SetTransform({ { PosX, 0.0f }, WinScale * Scale });
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
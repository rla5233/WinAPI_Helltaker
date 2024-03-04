#include "Piston.h"

bool Piston::IsLoad = false;

const FVector Piston::Scale = { 0.125f, 0.74f };
const float Piston::TurnInter = 0.02f;

Piston::Piston()
{
}

Piston::~Piston()
{
}

void Piston::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TPiston.png");

		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Piston", "Sin_LPiston");
		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Piston", "Sin_RPiston");

		IsLoad = true;
	}

	LT_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	LT_ImageRenderer->SetImage("Sin_LPiston");
	LT_ImageRenderer->CreateAnimation("LT_Turn", "Sin_LPiston", 6, 11, TurnInter, false);
	
	RT_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	RT_ImageRenderer->SetImage("Sin_RPiston");
	RT_ImageRenderer->CreateAnimation("RT_Turn", "Sin_RPiston", 6, 11, TurnInter, false);

	LB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	LB_ImageRenderer->SetImage("Sin_LPiston");
	LB_ImageRenderer->CreateAnimation("LB_Turn", "Sin_LPiston", 0, 5, TurnInter, false);
	
	RB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	RB_ImageRenderer->SetImage("Sin_RPiston");
	RB_ImageRenderer->CreateAnimation("RT_Turn", "Sin_RPiston", 0, 5, TurnInter, false);
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

void Piston::MoveStart()
{
	
}

void Piston::Move(float _DeltaTime)
{

}

void Piston::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);
	
	StateUpdate(_DeltaTime);
}

void Piston::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinPistonState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinPistonState::Move:
		Move(_DeltaTime);
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
		case ESinPistonState::Move:
			MoveStart();
			break;
		}
	}

	State = _State;
}
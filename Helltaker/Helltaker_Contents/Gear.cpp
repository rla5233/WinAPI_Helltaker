#include "Gear.h"

bool Gear::IsLoad = false;
const FVector Gear::Scale = { 0.208f, 0.278f };
const float Gear::WorkingInter = 0.016f;
const float Gear::WorkingSlowInter = 0.08f;

Gear::Gear()
{
}

Gear::~Gear()
{
}

void Gear::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_LGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_RGears_001.png");
		
		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Gear", "Sin_LGear");
		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Gear", "Sin_RGear");

		IsLoad = true;
	}

	L_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	R_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
}

void Gear::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.396f;
	
	L_ImageRenderer->SetImage("Sin_LGears_001.png");
	L_ImageRenderer->SetTransform({ { -PosX, 0.0f } , WinScale * Scale });
	
	R_ImageRenderer->SetImage("Sin_RGears_001.png");
	R_ImageRenderer->SetTransform({ { PosX, 0.0f } , WinScale * Scale });
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
	L_ImageRenderer->CreateAnimation("L_Working", "Sin_LGear", 0, 14, WorkingInter, true);
	L_ImageRenderer->CreateAnimation("L_WorkingSlow", "Sin_LGear", 0, 14, WorkingSlowInter, true);
	L_ImageRenderer->AnimationReset();
	L_ImageRenderer->ChangeAnimation("L_WorkingSlow");

	R_ImageRenderer->CreateAnimation("R_Working", "Sin_RGear", 0, 14, WorkingInter, true);
	R_ImageRenderer->CreateAnimation("R_WorkingSlow", "Sin_RGear", 0, 14, WorkingSlowInter, true);
	R_ImageRenderer->AnimationReset();
	R_ImageRenderer->ChangeAnimation("R_WorkingSlow");

	WorkOrder = 0;
}

void Gear::Working(float _DeltaTime)
{
	switch (WorkOrder)
	{
	case 0:
		Working1();
		break;
	case 1:
		Working2();
		break;
	}
}

void Gear::Working1()
{
	if (8 == L_ImageRenderer->GetCurAnimationFrame())
	{
		L_ImageRenderer->AnimationReset();
		L_ImageRenderer->ChangeAnimation("L_Working", false, 9);	
		
		R_ImageRenderer->AnimationReset();
		R_ImageRenderer->ChangeAnimation("R_Working", false, 9);
	}
}

void Gear::Working2()
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
#include "SuccessSkel.h"

bool SuccessSkel::IsLoad = false;
const FVector SuccessSkel::Scale = { 0.3333f, 0.5074f };
const float SuccessSkel::PosX = 0.334f;
const float SuccessSkel::SuccessInter = 0.08f;
const float SuccessSkel::IdleInter = 0.06f;

SuccessSkel::SuccessSkel()
{
}

SuccessSkel::~SuccessSkel()
{
}

void SuccessSkel::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Scene\\Dialogue\\Skeleton", "L_Idle");
		ContentsHelper::LoadFolder("Scene\\Dialogue\\Skeleton", "R_Idle");
		ContentsHelper::LoadFolder("Scene\\Dialogue\\Skeleton", "L_Start");
		ContentsHelper::LoadFolder("Scene\\Dialogue\\Skeleton", "R_Start");
	
		IsLoad = true;
	}	

	L_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	R_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);

	L_ImageRenderer->SetImage("L_Idle");
	L_ImageRenderer->CreateAnimation("L_Start", "L_Start", 0, 15, SuccessInter, false);
	L_ImageRenderer->CreateAnimation("L_Idle", "L_Idle", 0, 7, IdleInter, true);

	R_ImageRenderer->SetImage("R_Idle");
	R_ImageRenderer->CreateAnimation("R_Start", "R_Start", 0, 15, SuccessInter, false);
	R_ImageRenderer->CreateAnimation("R_Idle", "R_Idle", 0, 7, IdleInter, true);
}

void SuccessSkel::StartStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	L_ImageRenderer->AnimationReset();
	L_ImageRenderer->ChangeAnimation("L_Start");
	L_ImageRenderer->SetTransform({ { WinScale.X * (-PosX), 0.0f }, WinScale * Scale});
	L_ImageRenderer->ActiveOn();

	R_ImageRenderer->AnimationReset();
	R_ImageRenderer->ChangeAnimation("R_Start");
	R_ImageRenderer->SetTransform({ { WinScale.X * PosX, 0.0f }, WinScale * Scale});
	R_ImageRenderer->ActiveOn();
}

void SuccessSkel::Start()
{
	if (true == L_ImageRenderer->IsCurAnimationEnd()
	 && true == R_ImageRenderer->IsCurAnimationEnd())
	{
		StateChange(ESinSkelState::Idle);
		return;
	}
}

void SuccessSkel::IdleStart()
{
	L_ImageRenderer->AnimationReset();
	L_ImageRenderer->ChangeAnimation("L_Idle");

	R_ImageRenderer->AnimationReset();
	R_ImageRenderer->ChangeAnimation("R_Idle");
}

void SuccessSkel::Idle()
{
}

void SuccessSkel::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate();
}

void SuccessSkel::StateUpdate()
{
	switch (State)
	{
	case ESinSkelState::Start:
		Start();
		break;
	case ESinSkelState::Idle:
		Idle();
		break;
	}
}

void SuccessSkel::StateChange(ESinSkelState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinSkelState::Start:
			StartStart();
			break;
		case ESinSkelState::Idle:
			IdleStart();
			break;
		}
	}

	State = _State;
}
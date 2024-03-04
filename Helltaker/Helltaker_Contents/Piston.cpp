#include "Piston.h"

#include "Skull.h"
#include "SinChapterManager.h"

bool Piston::IsLoad = false;

const FVector Piston::Scale = { 0.125f, 0.74f };
const float Piston::TurnInter = 0.02f;
const float Piston::TurnDelayTime = 0.1f;

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
	LT_ImageRenderer->CreateAnimation("LT_Turn", "Sin_LPiston", 7, 13, TurnInter, false);
	
	RT_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	RT_ImageRenderer->SetImage("Sin_RPiston");
	RT_ImageRenderer->CreateAnimation("RT_Turn", "Sin_RPiston", 7, 13, TurnInter, false);

	LB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	LB_ImageRenderer->SetImage("Sin_LPiston");
	LB_ImageRenderer->CreateAnimation("LB_Turn", "Sin_LPiston", 0, 6, TurnInter, false);
	
	RB_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	RB_ImageRenderer->SetImage("Sin_RPiston");
	RB_ImageRenderer->CreateAnimation("RB_Turn", "Sin_RPiston", 0, 6, TurnInter, false);
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
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = GetActorLocation();
	FVector TargetPos = { CurPos.X, WinScale.Y * 0.2f };
	SetLerfStartPos(CurPos);
	SetLerfTargetPos(TargetPos);
	LerfMoveOn();

	TimeCount = TurnDelayTime;
	MoveOrder = 0;
}

void Piston::Move(float _DeltaTime)
{
	switch (MoveOrder)
	{
	case 0 :
		Move1(_DeltaTime);
		break;
	case 1:
		Move2(_DeltaTime);
		break;
	case 2:
		Move3(_DeltaTime);
		break;
	}
}

void Piston::Move1(float _DeltaTime)
{
	LerfMoveUpdate(_DeltaTime, 4.0f);
	if (false == IsLerfMoveOn())
	{
		if (0.0f >= TimeCount)
		{
			LT_ImageRenderer->AnimationReset();
			LT_ImageRenderer->ChangeAnimation("LT_Turn");
			RT_ImageRenderer->AnimationReset();
			RT_ImageRenderer->ChangeAnimation("RT_Turn");

			LB_ImageRenderer->AnimationReset();
			LB_ImageRenderer->ChangeAnimation("LB_Turn");
			RB_ImageRenderer->AnimationReset();
			RB_ImageRenderer->ChangeAnimation("RB_Turn");
			
			++MoveOrder;
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void Piston::Move2(float _DeltaTime)
{
	if (true == LT_ImageRenderer->IsCurAnimationEnd() &&
		true == LB_ImageRenderer->IsCurAnimationEnd() &&
		true == RT_ImageRenderer->IsCurAnimationEnd() &&
		true == RB_ImageRenderer->IsCurAnimationEnd())
	{
		SwitchLerfPos();
		LerfMoveOn();

		FVector MoveDistance = GetLerfTargetPos() - GetLerfStartPos();
		GetSinChapter()->GetSkull()->StateChange(ESinSkullState::Move, MoveDistance);

		++MoveOrder;
	}
}
	
void Piston::Move3(float _DeltaTime)
{
	LerfMoveUpdate(_DeltaTime, 4.0f);

	if (false == IsLerfMoveOn())
	{
		StateChange(ESinPistonState::Idle);
	}
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
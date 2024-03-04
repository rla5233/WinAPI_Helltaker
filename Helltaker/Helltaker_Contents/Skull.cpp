#include "Skull.h"

bool Skull::IsLoad = false;

const FVector Skull::SkullScale = { 0.212f, 0.396f };
const FVector Skull::ArmScale = { 0.206f, 0.17f };

Skull::Skull()
{
}

Skull::~Skull()
{
}

void Skull::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BSkull.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TSkull.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LArm.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RArm.png");

		IsLoad = true;
	}

	LB_SkullRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Mid);
	RB_SkullRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Mid);
	LT_SkullRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	RT_SkullRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	L_ArmRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
	R_ArmRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Bottom);
}

void Skull::SetSkull()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.412f;
	LB_SkullRenderer->SetImage("Sin_BSkull.png");
	LB_SkullRenderer->SetTransform({ { -PosX, 0.0f },  WinScale * SkullScale });

	RB_SkullRenderer->SetImage("Sin_BSkull.png");
	RB_SkullRenderer->SetTransform({ { PosX, 0.0f },  WinScale * SkullScale });


	LT_SkullRenderer->SetImage("Sin_TSkull.png");
	LT_SkullRenderer->SetTransform({ { -PosX, 0.0f },  WinScale * SkullScale });

	RT_SkullRenderer->SetImage("Sin_TSkull.png");
	RT_SkullRenderer->SetTransform({ { PosX, 0.0f },  WinScale * SkullScale });
}

void Skull::SetArm()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { WinScale.X * 0.306f, WinScale.Y * 0.04f };

	L_ArmRenderer->SetImage("Sin_LArm.png");
	L_ArmRenderer->SetTransform({ { -Pos.X, Pos.Y },  WinScale * ArmScale });

	R_ArmRenderer->SetImage("Sin_RArm.png");
	R_ArmRenderer->SetTransform({ { Pos.X, Pos.Y },  WinScale * ArmScale });
}

void Skull::IdleStart()
{
	SetSkull();
	SetArm();
}

void Skull::Idle(float _DeltaTime)
{
}

void Skull::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Skull::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSkullState::Idle:
		Idle(_DeltaTime);
		break;
	}
}

void Skull::StateChange(ESinSkullState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinSkullState::Idle:
			IdleStart();
			break;
		}
	}

	State = _State;
}
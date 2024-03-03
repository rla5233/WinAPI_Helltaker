#include "Shield.h"

bool Shield::IsLoad = false;

const FVector Shield::B_Scale = { 0.406f, 0.686f };
const FVector Shield::T_Scale = { 0.2786f, 0.296f };

Shield::Shield()
{
}

Shield::~Shield()
{
}

void Shield::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LShield.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RShield.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LTShield.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RTShield.png");

		IsLoad = true;
	}

	LB_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	RB_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	LT_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	RT_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);

	SetShield();
}

void Shield::SetShield()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float B_PosX = WinScale.X * 0.177f;
	FVector T_Pos = { WinScale.X * 0.1132f, WinScale.Y * (-0.1949f) };

	LB_ImageRenderer->SetImage("Sin_LShield.png");
	LB_ImageRenderer->SetTransform({ { -B_PosX, 0.0f }, WinScale * B_Scale });

	RB_ImageRenderer->SetImage("Sin_RShield.png");
	RB_ImageRenderer->SetTransform({ { B_PosX, 0.0f }, WinScale * B_Scale });

	LT_ImageRenderer->SetImage("Sin_LTShield.png");
	LT_ImageRenderer->SetTransform({ { -T_Pos.X, T_Pos.Y }, WinScale * T_Scale });

	RT_ImageRenderer->SetImage("Sin_RTShield.png");
	RT_ImageRenderer->SetTransform({ { T_Pos.X, T_Pos.Y }, WinScale * T_Scale });
}

void Shield::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);
}
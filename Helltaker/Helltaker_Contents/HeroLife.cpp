#include "HeroLife.h"

bool HeroLife::IsLoad = false;

const FVector HeroLife::PanelScale = { 0.39f, 0.133f };

const FVector HeroLife::EyeScale = { 0.167f, 0.167f };

const FVector HeroLife::PyreScale = { 0.13f, 0.111f };

const FVector HeroLife::FireScale = { 0.0625f, 0.107f };
const float HeroLife::FireInter = 0.06f;



HeroLife::HeroLife()
{
}

HeroLife::~HeroLife()
{
}

void HeroLife::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LPanel.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RPanel.png");

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Eye.png");

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pyre_On.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pyre_Off.png");

		ContentsHelper::LoadFolder("Chapter\\Component", "Sin_Fire");

		IsLoad = true;
	}

	L_PanelRenderer = CreateImageRenderer(SinRenderOrder::Top);
	R_PanelRenderer = CreateImageRenderer(SinRenderOrder::Top);
	EyeRenderer = CreateImageRenderer(SinRenderOrder::Top);

	PyreRenderer.reserve(4);
	FireRenderer.reserve(4);
	for (int i = 0; i < 4; i++)
	{
		PyreRenderer[i] = CreateImageRenderer(SinRenderOrder::Top);
		FireRenderer[i] = CreateImageRenderer(SinRenderOrder::Top);
	}
}

void HeroLife::SetPanel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.228f;

	L_PanelRenderer->SetImage("Sin_LPanel.png");
	L_PanelRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * PanelScale });

	L_PanelRenderer->SetImage("Sin_RPanel.png");
	L_PanelRenderer->SetTransform({ { PosX, 0.0f }, WinScale * PanelScale });
}

void HeroLife::SetEye()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * (-0.005f);

	EyeRenderer->SetImage("Sin_Eye.png");
	EyeRenderer->SetTransform({ { 0.0f, PosY }, WinScale * EyeScale })
}

void HeroLife::IdleStart()
{
	SetPanel();

}

void HeroLife::Idle(float _DeltaTime)
{
}

void HeroLife::HitStart()
{
}

void HeroLife::Hit(float _DeltaTime)
{
}

void HeroLife::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);
}

void HeroLife::StateUpdate(float _DeltaTime)
{
}

void HeroLife::StateChange(ESinHeroLifeState _State)
{
}



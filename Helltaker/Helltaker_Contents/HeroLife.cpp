#include "HeroLife.h"

bool HeroLife::IsLoad = false;

static const FVector PyreScale = { 0.13f, 0.111f };

static const FVector FireScale = { 0.0625f, 0.107f };
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

void HeroLife::IdleStart()
{

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



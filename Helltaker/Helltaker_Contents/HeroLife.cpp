#include "HeroLife.h"

bool HeroLife::IsLoad = false;

const float HeroLife::SinFireInter = 0.06f;

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



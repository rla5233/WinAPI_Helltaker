#include "HitChainHp.h"

HitChainHp::HitChainHp()
{
}

HitChainHp::~HitChainHp()
{
}

void HitChainHp::BeginPlay()
{
	RenderActor::BeginPlay();
	
	L_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	R_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	Hp_Renderer = CreateImageRenderer(SinRenderOrder::Top);
	TextRenderer = CreateImageRenderer(SinRenderOrder::Top);
}

void HitChainHp::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

}

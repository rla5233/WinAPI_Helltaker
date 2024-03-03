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
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LShield_Top.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RShield_Top.png");

		IsLoad = true;
	}

	LB_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	RB_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	LT_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	RT_ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);


}

void Shield::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);
}

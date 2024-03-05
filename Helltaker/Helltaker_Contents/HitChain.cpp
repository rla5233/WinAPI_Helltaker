#include "HitChain.h"

const FVector HitChain::Scale = { 0.0f, 0.0f };
bool HitChain::IsLoad = false;

HitChain::HitChain()
{
}

HitChain::~HitChain()
{
}

void HitChain::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LHitChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RHitChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LBrokenChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RBrokenChain.png");

		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
}

void HitChain::IdleStart()
{
	switch (Type)
	{
	case ESinHitChainType::Left:
		ImageRenderer->SetImage("Sin_LHitChain.png");
		break;
	case ESinHitChainType::Right:
		ImageRenderer->SetImage("Sin_RHitChain.png");
		break;
	}

	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ {0.0f} {} })
}

void HitChain::Idle(float _DeltaTime)
{}

void HitChain::HitStart()
{}

void HitChain::Hit(float _DeltaTime)
{}

void HitChain::DeathStart()
{}

void HitChain::Death(float _DeltaTime)
{}

void HitChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);
}

void HitChain::StateUpdate(float _DeltaTime)
{}

void HitChain::StateChange(ESinHitChainState _State)
{}


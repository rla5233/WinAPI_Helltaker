#include "HitChainHp.h"

const FVector HitChainHp::ImageScale = { 0.208f, 0.0926f };
const FVector HitChainHp::HpScale = { 0.28f, 0.008f };

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
	
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ImgPosX = WinScale.X * 0.086f;
	L_ImageRenderer->SetImage("Small_LButton.png");
	L_ImageRenderer->SetTransform({ { -ImgPosX, 0.0f }, WinScale * ImageScale });
	R_ImageRenderer->SetImage("Small_RButton.png");
	R_ImageRenderer->SetTransform({ { ImgPosX, 0.0f }, WinScale * ImageScale });
	Hp_Renderer->SetImage("White_Bar.png");
	Hp_Renderer->SetTransform({ { 0.0f, -2.0f }, WinScale * HpScale });
}

void HitChainHp::IdleStart()
{}

void HitChainHp::Idle(float _DeltaTime)
{}

void HitChainHp::HitStart()
{

}

void HitChainHp::Hit(float _DeltaTime)
{}

void HitChainHp::DeathStart()
{}

void HitChainHp::Death(float _DeltaTime)
{}

void HitChainHp::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void HitChainHp::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinHitChainHpState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinHitChainHpState::Hit:
		Hit(_DeltaTime);
		break;
	case ESinHitChainHpState::Death:
		Death(_DeltaTime);
		break;
	}
}

void HitChainHp::StateChange(ESinHitChainHpState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinHitChainHpState::Idle:
			IdleStart();
			break;
		case ESinHitChainHpState::Hit:
			HitStart();
			break;
		case ESinHitChainHpState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}

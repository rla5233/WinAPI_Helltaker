#include "HeroLife.h"

#include "SinChapterManager.h"
#include "Sin_Hero.h"

#include <EngineCore\EngineResourcesManager.h>

bool HeroLife::IsLoad = false;

const FVector HeroLife::PanelScale = { 0.39f, 0.133f };
const FVector HeroLife::WheelScale = { 0.2604f, 0.463f };
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

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Wheel.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Wheel_Mask.bmp");
		
		UWindowImage* Rot = UEngineResourcesManager::GetInst().FindImg("Sin_Wheel.png");
		UWindowImage* Mask = UEngineResourcesManager::GetInst().FindImg("Sin_Wheel_Mask.bmp");
		Rot->SetRotationMaskImage(0, Mask, 0);

		IsLoad = true;
	}

	WheelRenderer = CreateImageRenderer(SinRenderOrder::Top);
	L_PanelRenderer = CreateImageRenderer(SinRenderOrder::Top);
	R_PanelRenderer = CreateImageRenderer(SinRenderOrder::Top);
	EyeRenderer = CreateImageRenderer(SinRenderOrder::Top);

	PyreRenderer.reserve(4);
	FireRenderer.reserve(4);
	for (int i = 0; i < 4; i++)
	{
		PyreRenderer.push_back(CreateImageRenderer(SinRenderOrder::Top));
		FireRenderer.push_back(CreateImageRenderer(SinRenderOrder::Top));
		FireRenderer[i]->SetImage("Sin_Fire");
		FireRenderer[i]->CreateAnimation("Sin_Fire", "Sin_Fire", 0, 11, FireInter, true);
	}
}

void HeroLife::SetPanel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.228f;

	L_PanelRenderer->SetImage("Sin_LPanel.png");
	L_PanelRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * PanelScale });

	R_PanelRenderer->SetImage("Sin_RPanel.png");
	R_PanelRenderer->SetTransform({ { PosX, 0.0f }, WinScale * PanelScale });
}

void HeroLife::SetEye()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * (-0.005f);

	EyeRenderer->SetImage("Sin_Eye.png");
	EyeRenderer->SetTransform({ { 0.0f, PosY }, WinScale * EyeScale });
}

void HeroLife::SetPyre()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * (-0.245f);

	const float IntervalX = WinScale.X * 0.111f;

	int idx = 0;
	for (int i = 0; i < 2; i++)
	{
		PyreRenderer[idx]->SetImage("Sin_Pyre_On.png");
		PyreRenderer[idx]->SetTransform({ { PosX + (IntervalX * i), 0.0f}, WinScale * PyreScale});

		++idx;
	}

	PosX = WinScale.X * 0.134f;
	for (int i = 0; i < 2; i++)
	{
		PyreRenderer[idx]->SetImage("Sin_Pyre_On.png");
		PyreRenderer[idx]->SetTransform({ { PosX + (IntervalX * i), 0.0f}, WinScale * PyreScale });

		++idx;
	}
}

void HeroLife::SetFire()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * (-0.245f);
	float PosY = WinScale.Y * (-0.035f);

	const float IntervalX = WinScale.X * 0.111f;

	int idx = 0;
	for (int i = 0; i < 2; i++)
	{
		FireRenderer[idx]->SetTransform({ { PosX + (IntervalX * i), PosY}, WinScale * FireScale });
		FireRenderer[idx]->AnimationReset();
		FireRenderer[idx]->ChangeAnimation("Sin_Fire");
		
		++idx;
	}

	PosX = WinScale.X * 0.134f;
	for (int i = 0; i < 2; i++)
	{
		FireRenderer[idx]->SetTransform({ { PosX + (IntervalX * i), PosY}, WinScale * FireScale });
		FireRenderer[idx]->AnimationReset();
		FireRenderer[idx]->ChangeAnimation("Sin_Fire");

		++idx;
	}
}

void HeroLife::SetWheel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.152f;
	
	WheelRenderer->SetImage("Sin_Wheel.png");
	WheelRenderer->SetTransform({ { 0.0f, PosY }, WinScale * WheelScale });

	float Angle = (360.0f / -5.0f) * (SinChapterNum - 1.0f) + 1.0f;
	WheelRenderer->SetAngle(Angle);
}

void HeroLife::IdleStart()
{
	SetPanel();
	SetEye();
	SetPyre();
	SetFire();
	SetWheel();
}

void HeroLife::Idle(float _DeltaTime)
{
	WheelTurnUpdate(_DeltaTime);
}

void HeroLife::WheelTurnUpdate(float _DeltaTime)
{

}

void HeroLife::HeroHitStart()
{
	int HeroLife = GetSinChapter()->GetPlayerHero()->GetLife();
	int idx = static_cast<int>(PyreRenderer.size()) - HeroLife - 1;

	PyreRenderer[idx]->SetImage("Sin_Pyre_Off.png");
	FireRenderer[idx]->ActiveOff();
}

void HeroLife::HeroHit(float _DeltaTime)
{
	State = ESinHeroLifeState::Idle;
}

void HeroLife::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void HeroLife::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinHeroLifeState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinHeroLifeState::HeroHit:
		HeroHit(_DeltaTime);
		break;
	}
}

void HeroLife::StateChange(ESinHeroLifeState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinHeroLifeState::Idle:
			IdleStart();
			break;
		case ESinHeroLifeState::HeroHit:
			HeroHitStart();
			break;
		}
	}

	State = _State;
}



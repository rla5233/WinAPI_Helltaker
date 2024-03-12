#include "Sin_Demon.h"

#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineSound.h>

bool Sin_Demon::IsLoad = false;

const FVector Sin_Demon::Scale = { 0.0521f, 0.093f };
const FVector Sin_Demon::AppearScale = { 0.0521f, 0.241f };
const float Sin_Demon::AppearInter = 0.065f;

const FVector Sin_Demon::LandEffectScale = { 0.0375f, 0.0444f };

Sin_Demon::Sin_Demon()
{
}

Sin_Demon::~Sin_Demon()
{
}

void Sin_Demon::BeginPlay()
{
	Demon::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Demon", "Judge_Jump");

		ContentsHelper::LoadSound("Sound\\Effect", "boss_judgement_land.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "demon_capture_002.wav");

		IsLoad = true;
	}
}

void Sin_Demon::SetDemon(std::string_view _Name, const FTransform& _FTransform)
{
	std::string AnimationName = _Name.data();
	AnimationName += "_Idle";
	ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	ImageRenderer->SetImage(_Name);
	ImageRenderer->SetTransform(_FTransform);
	ImageRenderer->CreateAnimation(AnimationName, _Name, 0, 11, IdleInter, true);
	StarEffect::TargetPos = ImageRenderer->GetPosition();
}

void Sin_Demon::Tick(float _DeltaTime)
{
	Demon::Tick(_DeltaTime);
}

void Sin_Demon::VictoryStart()
{
	Demon::VictoryStart();
	
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 0.052f, 0.093f };
	FVector Pos = { 0.0f, 0.0f };
	ImageRenderer->AnimationReset();
	ImageRenderer->CreateAnimation("Jud_Idle", "Judge", 0, 11, IdleInter, true);
	ImageRenderer->ChangeAnimation("Jud_Idle");
	ImageRenderer->SetTransform({ WinScale * Pos, WinScale * Scale });
}

void Sin_Demon::CreateStarEffect()
{
	Demon::CreateStarEffect();
	AllStarEffect.rbegin()->EffectRenderer->SetOrder(static_cast<int>(SinRenderOrder::Top));
}

void Sin_Demon::CreateLovePlosion(float _DeltaTime)
{
	Demon::CreateLovePlosion(_DeltaTime);
	
	if (nullptr != LovePlosionRenderer)
	{
		LovePlosionRenderer->SetOrder(static_cast<int>(SinRenderOrder::Top));
	}
}

void Sin_Demon::Sin_AppearStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->CreateAnimation("Judge_Appear", "Judge_Jump", 0, 8, IdleInter, false);
	ImageRenderer->SetTransform({ { 0.0f, 0.0f }, WinScale * AppearScale });
	ImageRenderer->AnimationReset();
	ImageRenderer->ChangeAnimation("Judge_Appear");
	ImageRenderer->ActiveOn();
	
	CreateLandEffect();
	ImageRenderer->SetOrder(static_cast<int>(SinRenderOrder::Top));
	UEngineSound::SoundPlay("boss_judgement_land.wav");
	OrderCount = 0;
}

void Sin_Demon::Sin_Appear(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		LandEffectRender();
		break;
	case 1:
		LandEffectEndCheck();
		break;
	}
}

void Sin_Demon::CreateLandEffect()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos1 = { -0.02f, 0.02f };
	UImageRenderer* Renderer1 = CreateImageRenderer(SinRenderOrder::Top);
	Renderer1->SetImage("Move");
	Renderer1->CreateAnimation("Land_Effect", "Move", 0, 2, AppearInter, false);
	Renderer1->SetTransform({ WinScale * Pos1, WinScale * LandEffectScale });
	Renderer1->ActiveOff();

	LandEffect.push_back(Renderer1);

	UImageRenderer* Renderer2 = CreateImageRenderer(SinRenderOrder::Top);
	FVector Pos2 = { -0.015f, 0.05f };
	Renderer2->SetImage("Move");
	Renderer2->CreateAnimation("Land_Effect", "Move", 3, 5, AppearInter, false);
	Renderer2->SetTransform({ WinScale * Pos2, WinScale * LandEffectScale });
	Renderer2->ActiveOff();

	LandEffect.push_back(Renderer2);

	UImageRenderer* Renderer3 = CreateImageRenderer(SinRenderOrder::Top);
	FVector Pos3 = { 0.018f, 0.018f };
	Renderer3->SetImage("Move");
	Renderer3->CreateAnimation("Land_Effect", "Move", 6, 8, AppearInter, false);
	Renderer3->SetTransform({ WinScale * Pos3, WinScale * LandEffectScale });
	Renderer3->ActiveOff();
	
	LandEffect.push_back(Renderer3);
}

void Sin_Demon::LandEffectRender()
{
	if (1 == ImageRenderer->GetCurAnimationFrame())
	{
		for (UImageRenderer* Renderer : LandEffect)
		{
			if (nullptr == Renderer)
			{
				MsgBoxAssert("Renderer is nullptr");
			}

			Renderer->AnimationReset();
			Renderer->ChangeAnimation("Land_Effect");
			Renderer->ActiveOn();
		}

		++OrderCount;
		RenderEndCount = 0;
	}
}

void Sin_Demon::LandEffectEndCheck()
{
	for (UImageRenderer* Renderer : LandEffect)
	{
		if (nullptr == Renderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		if (true == Renderer->IsCurAnimationEnd())
		{
			Renderer->ActiveOff();
			++RenderEndCount;
		}
	}

	if (3 == RenderEndCount)
	{
		for (UImageRenderer* Renderer : LandEffect)
		{
			if (nullptr == Renderer)
			{
				MsgBoxAssert("Renderer is nullptr");
			}

			Renderer->Destroy();
		}

		LandEffect.clear();
		++OrderCount;
	}
}

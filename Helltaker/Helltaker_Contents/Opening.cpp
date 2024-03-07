#include "Opening.h"

#include "BackGround.h"
#include "Scene.h"
#include "MainMenu.h"

const float Opening::FadeOutDelayTime = 0.3f;

Opening::Opening()
{
}

Opening::~Opening()
{
}

void Opening::BeginPlay()
{
	ULevel::BeginPlay();

	ContentsHelper::LoadImg("Scene\\Dialogue", "UnityLogo.png");
	ContentsHelper::LoadImg("Background", "OpeningBG.png");
}

void Opening::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	switch (OpeningOrder)
	{
	case 0:
		LogoFadeIn(_DeltaTime);
		break;
	case 1:
		DelayTime(_DeltaTime);
		break;
	case 2:
		LogoFadeOut(_DeltaTime);
		break;
	case 3:
		EnterMainMenu();
		break;
	}
}

void Opening::LogoFadeIn(float _DeltaTime)
{
	UnityLogo->FadeInUpdate(UnityLogo->GetImageRenderer(), _DeltaTime, 0.9f);
	if (false == UnityLogo->IsFadeInOn())
	{
		UnityLogo->FadeOutOn();
		DelayTimeCount = FadeOutDelayTime;
		++OpeningOrder;
	}
}

void Opening::DelayTime(float _DeltaTime)
{
	if (0.0f >= DelayTimeCount)
	{
		++OpeningOrder;
		return;
	}

	DelayTimeCount -= _DeltaTime;
}

void Opening::LogoFadeOut(float _DeltaTime)
{
	UnityLogo->FadeOutUpdate(UnityLogo->GetImageRenderer(), _DeltaTime, 0.9f);
	if (false == UnityLogo->IsFadeOutOn())
	{
		++OpeningOrder;
	}
}

void Opening::EnterMainMenu()
{
	GEngine->CreateLevel<MainMenu>("MainMenu");
	GEngine->ChangeLevel("MainMenu");
}

void Opening::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	FVector WinScale = ContentsHelper::GetWindowScale();
	OpeningBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	OpeningBG->CreateBackGround("OpeningBG");

	UnityLogo = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	UnityLogo->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.522f });
	UnityLogo->SetName("UnityLogo");
	UnityLogo->CreateImageRenderer(RenderOrder::Scene);
	UnityLogo->GetImageRenderer()->SetImage(UnityLogo->GetName() + ".png");
	UnityLogo->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.25f, WinScale.Y * 0.225f } });
	UnityLogo->GetImageRenderer()->SetAlpha(0.0f);
	UnityLogo->FadeInOn();

	OpeningOrder = 0;
}

void Opening::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	OpeningBG->Destroy();
	OpeningBG = nullptr;
	UnityLogo->Destroy();
	UnityLogo = nullptr;
}
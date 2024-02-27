#include "Opening.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Scene.h"
#include "MainMenu.h"

#include <EnginePlatform/EngineWindow.h>

Opening::Opening()
{
}

Opening::~Opening()
{

}
// 수정 (리팩토링 가능?)
void Opening::BeginPlay()
{
	ULevel::BeginPlay();

	ContentsHelper::LoadImg("Scene\\Dialogue", "UnityLogo.png");
	ContentsHelper::LoadImg("Background", "OpeningBG.png");
	//ContentsHelper::LoadSound("Sound", "Vitality.wav");
}

void Opening::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	FVector WinScale = ContentsHelper::GetWindowScale();

	UnityLogo->FadeInUpdate(_DeltaTime, 0.002f);
	UnityLogo->FadeInUpdate(_DeltaTime, 0.002f);

	//TimeCount += _DeltaTime;
	//
	//if (2 <= TimeCount)
	//{
	//	GEngine->CreateLevel<MainMenu>("MainMenu");
	//	GEngine->ChangeLevel("MainMenu");
	//}
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
	UnityLogo->FadeInOn();

	//ContentsHelper::SoundPlay("Vitality.wav");
}

void Opening::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	OpeningBG->Destroy();
	OpeningBG = nullptr;
	UnityLogo->Destroy();
	UnityLogo = nullptr;
}

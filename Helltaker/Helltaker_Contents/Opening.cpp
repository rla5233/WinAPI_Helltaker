#include "Opening.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Dialogue.h"
#include "MainMenu.h"

#include <EnginePlatform/EngineWindow.h>

Opening::Opening()
{
}

Opening::~Opening()
{
}

void Opening::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* OpeningBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	OpeningBG->CreateBackGround("OpeningBG.png");

	Dialogue* UnityLogo = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	UnityLogo->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.9f});
	UnityLogo->SetName("UnityLogo.png");
	UnityLogo->LoadImg("Secene\\Dialogue");
	UnityLogo->CreateImageRenderer(RenderOrder::Dialogue);
	UnityLogo->SetImg(UnityLogo->GetName());
	UnityLogo->SetTransform({ {0, 0}, {WinScale.X / 4.0f, WinScale.Y / 4.0f } });
}

void Opening::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
	TimeCount += _DeltaTime;

	if (2 <= TimeCount)
	{
		GEngine->CreateLevel<MainMenu>("MainMenu");
		GEngine->ChangeLevel("MainMenu");
	}
}
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
	OpeningBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	OpeningBG->SetName("OpeningBG.png");
	OpeningBG->LoadImg("BackGround");
	OpeningBG->CreateImageRenderer(RenderOrder::BackGround);
	OpeningBG->SetImg(OpeningBG->GetName());
	OpeningBG->SetTransform({ {0, 0}, WinScale });

	// 여기 부터 시작
	Dialogue* UnityLogo = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	UnityLogo->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	UnityLogo->SetName("UnityLogo.png");
	UnityLogo->SetScale({ WinScale.X / 5, WinScale.Y / 5 });
	UnityLogo->LoadImg();
	UnityLogo->SetImg(false);
}

void Opening::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
	TimeCount += _DeltaTime;

	//if (2 <= TimeCount)
	//{
	//	GEngine->CreateLevel<MainMenu>("MainMenu");
	//	GEngine->ChangeLevel("MainMenu");
	//}
}
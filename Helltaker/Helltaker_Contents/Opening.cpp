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

	ContentsHelper::LoadImg("Secene\\Dialogue", "UnityLogo.png");
	ContentsHelper::LoadImg("Background", "OpeningBG.png");
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

void Opening::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* OpeningBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	OpeningBG->CreateBackGround("OpeningBG");
	AllActors.push_back(OpeningBG);

	Dialogue* UnityLogo = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	UnityLogo->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.9f });
	UnityLogo->SetName("UnityLogo");
	UnityLogo->CreateImageRenderer(RenderOrder::Dialogue);
	UnityLogo->GetRenderer()->SetImage(UnityLogo->GetName() + ".png");
	UnityLogo->GetRenderer()->SetTransform({ {0, 0}, {WinScale.X / 4.0f, WinScale.Y / 4.0f } });
	AllActors.push_back(UnityLogo);
}

void Opening::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	for (AActor* Actor : AllActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->Destroy(0.0f);
		Actor = nullptr;
	}

	AllActors.clear();
}

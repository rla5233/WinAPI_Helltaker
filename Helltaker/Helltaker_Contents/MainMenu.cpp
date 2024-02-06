#include "MainMenu.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Dialogue.h"
#include "Character.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageRenderer.h>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* DefaultBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	DefaultBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	DefaultBG->SetName("DefaultBG.png");
	DefaultBG->LoadImg();
	DefaultBG->SetImg();

	Dialogue* MainMenuDialogue = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	MainMenuDialogue->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2.45f });
	MainMenuDialogue->SetName("MainMenuDialogue_001.png");
	MainMenuDialogue->LoadImg();
	MainMenuDialogue->SetImg(true);

	Character* Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Dialogue));
	Beel->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2.45f });
	Beel->SetName("Beel_Fly.png");
	Beel->LoadImg();
	Beel->SetImg(true);
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void MainMenu::StateUpdate(float _DeltaTime)
{
	
}
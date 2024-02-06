#include "MainMenu.h"

#include "BackGround.h"
#include "Dialogue.h"
#include "Character.h"
#include "UI.h"

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

	Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Beel->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2.45f });
	Beel->SetName("Beel_Fly.png");
	Beel->LoadImg();

	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.X / 2, WinScale.Y / 1.15f });
	Booper->SetName("Booper");
	Booper->LoadFolder();	
	Booper->SetScale({ 30, 15 });
	Booper->SetImg(false);
	Booper->CreateUIAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->ChangeUIAnimation("Booper_Idle");

	StateChange(EMainMenuState::Begin);
}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void MainMenu::Enter(float _DeltaTime)
{
	
}

void MainMenu::SelectMenu(float _DeltaTime)
{}

void MainMenu::Exit(float _DeltaTime)
{}

void MainMenu::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMainMenuState::Enter:
		Enter(_DeltaTime);
		break;
	case EMainMenuState::SelectMenu:
		SelectMenu(_DeltaTime);
		break;
	case EMainMenuState::Exit:
		Exit(_DeltaTime);
		break;
	default:
	{
		if (EngineInput::IsPress(VK_SPACE) || EngineInput::IsPress(VK_RETURN))
		{
			StateChange(EMainMenuState::Enter);
			Beel->SetImg(true);
		}
		break;
	}
	}
}

void MainMenu::StateChange(EMainMenuState _State)
{
	State = _State;
}

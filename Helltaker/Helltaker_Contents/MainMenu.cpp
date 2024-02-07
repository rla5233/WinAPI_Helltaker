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
	DefaultBG->CreateBackGround("DefaultBG.png");

	Dialogue* MainMenuDialogue = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	MainMenuDialogue->SetActorLocation({ WinScale.X / 2.0f, WinScale.Y / 2.45f });
	MainMenuDialogue->SetName("MainMenuDialogue_001.png");
	MainMenuDialogue->LoadImg("Secene\\Dialogue");
	MainMenuDialogue->CreateImageRenderer(RenderOrder::Dialogue);
	MainMenuDialogue->SetImg(MainMenuDialogue->GetName());
	MainMenuDialogue->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 2.0f } });
	
	Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Beel->SetActorLocation({ WinScale.X / 2.0f, WinScale.Y / 2.9f });
	Beel->SetName("Beel_Fly.png");
	Beel->LoadImg("Secene\\Characters");
	
	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.X / 2.0f, WinScale.Y / 1.15f });
	Booper->SetName("Booper");
	Booper->LoadFolder("UI");
	Booper->CreateImageRenderer(RenderOrder::UI);
	Booper->SetImg(Booper->GetName());
	Booper->SetTransform({ {0, 0}, { WinScale.X / 36.0f, WinScale.Y / 45.0f } });
	Booper->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->ChangeAnimation("Booper_Idle");

	StateChange(EMainMenuState::Begin);
}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void MainMenu::Begin(float _DeltaTime)
{
	if (EngineInput::IsPress(VK_SPACE) || EngineInput::IsPress(VK_RETURN))
	{
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::Enter(float _DeltaTime)
{
	if (false == IsEnterInit)
	{
		EnterInit();
	}


	if (EngineInput::IsDown(VK_SPACE) || EngineInput::IsDown(VK_RETURN))
	{
		StateChange(EMainMenuState::SelectMenu);
		return;
	}
}

void MainMenu::EnterInit()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Beel->CreateImageRenderer(RenderOrder::Character);
	Beel->SetImg(Beel->GetName());
	Beel->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 1.44f} });
	IsEnterInit = true;
}

void MainMenu::SelectMenu(float _DeltaTime)
{
	if (false == IsSelectInit)
	{
		SelectInit();
	}

	SelectStart(_DeltaTime);
}

void MainMenu::SelectInit()
{
  	FVector WinScale = ContentsHelper::GetWindowScale();
	IsSelectInit = true;
}

void MainMenu::SelectStart(float _DeltaTime)
{
	Booper->RenderActiveOff();
}

void MainMenu::Exit(float _DeltaTime)
{}

void MainMenu::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMainMenuState::Begin:
		Begin(_DeltaTime);
		break;
	case EMainMenuState::Enter:
		Enter(_DeltaTime);
		break;
	case EMainMenuState::SelectMenu:
		SelectMenu(_DeltaTime);
		break;
	case EMainMenuState::Exit:
		Exit(_DeltaTime);
		break;
	}
}

void MainMenu::StateChange(EMainMenuState _State)
{
	State = _State;
}

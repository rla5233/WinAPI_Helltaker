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
	DefaultBG->CreateBackGround("DefaultBG");

	Dialogue* MainMenuDialogue = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	MainMenuDialogue->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.45f });
	MainMenuDialogue->SetName("MainMenuDialogue_001");
	MainMenuDialogue->LoadImg("Secene\\Dialogue");
	MainMenuDialogue->CreateImageRenderer(RenderOrder::Dialogue);
	MainMenuDialogue->SetImg(MainMenuDialogue->GetName() + ".png");
	MainMenuDialogue->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 2.0f } });
	
	Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Beel->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.9f });
	Beel->SetName("Beel_Fly");
	Beel->LoadImg("Secene\\Characters");
	
	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.15f});
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
	Beel->SetImg(Beel->GetName() + ".png");
	Beel->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 1.44f} });
	IsEnterInit = true;
}

void MainMenu::SelectMenu(float _DeltaTime)
{
	if (false == IsSelectMenuInit)
	{
		SelectMenuInit();
	}

	SelectMenuStart(_DeltaTime);
}

void MainMenu::SelectMenuInit()
{
   	FVector WinScale = ContentsHelper::GetWindowScale();
	
	MenuBarVec.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		MenuBarVec.push_back(SpawnActor<UI>(static_cast<int>(UpdateOrder::UI)));
	}

	MenuBarVec[0]->LoadImg("UI", "MenuBar_Unselected.png");
	float interval = 0.0f;
	for (UI* MenuBar : MenuBarVec)
	{
		MenuBar->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.27f + interval });
		MenuBar->SetName("MenuBar");
		MenuBar->CreateImageRenderer(RenderOrder::UI);
		MenuBar->SetImg("MenuBar_Unselected.png");
		MenuBar->SetTransform({ {0, 0}, {WinScale.X / 1.93f, WinScale.Y / 11.0f} });
		interval += WinScale.Y / 13.5f;
	}	

	IsSelectMenuInit = true;
}

void MainMenu::SelectMenuStart(float _DeltaTime)
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

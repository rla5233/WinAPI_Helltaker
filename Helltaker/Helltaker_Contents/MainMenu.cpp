#include "MainMenu.h"

#include "BackGround.h"
#include "Dialogue.h"
#include "Character.h"
#include "UI.h"
#include "Chapter1.h"


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

	ContentsHelper::LoadImg("BackGround", "DefaultBG.png");
	ContentsHelper::LoadImg("Secene\\Dialogue", "MainMenuDialogue_001.png");
	ContentsHelper::LoadImg("Secene\\Characters", "Beel_Fly.png");
	ContentsHelper::LoadFolder("UI", "Booper");
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* DefaultBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	DefaultBG->CreateBackGround("DefaultBG");
	AllActors.push_back(DefaultBG);

	Dialogue* MainMenuDialogue = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	MainMenuDialogue->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.45f });
	MainMenuDialogue->SetName("MainMenuDialogue_001");
	MainMenuDialogue->CreateImageRenderer(RenderOrder::Dialogue);
	MainMenuDialogue->SetImg(MainMenuDialogue->GetName() + ".png");
	MainMenuDialogue->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 2.0f } });
	AllActors.push_back(MainMenuDialogue);

	Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Beel->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.9f });
	Beel->SetName("Beel_Fly");	
	AllActors.push_back(Beel);

	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.15f });
	Booper->SetName("Booper");
	Booper->CreateImageRenderer(RenderOrder::UI);
	Booper->SetImg(Booper->GetName());
	Booper->SetTransform({ {0, 0}, { WinScale.X / 36.0f, WinScale.Y / 45.0f } });
	Booper->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->ChangeAnimation("Booper_Idle");
	AllActors.push_back(Booper);

	StateChange(EMainMenuState::Begin);
}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}


void MainMenu::Begin(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_SPACE) || UEngineInput::IsPress(VK_RETURN))
	{
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::Enter(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		StateChange(EMainMenuState::SelectMenu);
		return;
	}
}

void MainMenu::EnterStart()
{
	if (false == IsEnterInit)
	{
		EnterInit();
	}

	Beel->SetImg(Beel->GetName() + ".png");
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
	if (UEngineInput::IsDown('W') || UEngineInput::IsDown(VK_UP))
	{
		MenuBarVec[FocusMenuIndex]->SetImg("MenuBar_UnSelected.png");
		SetFocusMenuIndex(FocusMenuIndex - 1);
		MenuBarVec[FocusMenuIndex]->SetImg("MenuBar_Selected.png");
	}
	else if (UEngineInput::IsDown('S') || UEngineInput::IsDown(VK_DOWN))
	{
		MenuBarVec[FocusMenuIndex]->SetImg("MenuBar_UnSelected.png");
		SetFocusMenuIndex(FocusMenuIndex + 1);
		MenuBarVec[FocusMenuIndex]->SetImg("MenuBar_Selected.png");
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		switch (FocusMenuIndex)
		{
		case 0:
			StateChange(EMainMenuState::EnterChapter);
			SelectChapterNum = 1;
			break;
		case 1:
			//StateChange(EMainMenuState::SelectChapter);
			break;
		case 2:
			//StateChange(EMainMenuState::Exit);
			break;
		default:
			break;
		}
	}
}

void MainMenu::SelectMenuInit()
{
   	FVector WinScale = ContentsHelper::GetWindowScale();
	
	MenuBarVec.reserve(MenuBarCount);
	for (int i = 0; i < MenuBarCount; i++)
	{
		MenuBarVec.push_back(SpawnActor<UI>(static_cast<int>(UpdateOrder::UI)));
	}

	ContentsHelper::LoadImg("UI", "MenuBar_UnSelected.png");
	ContentsHelper::LoadImg("UI", "MenuBar_Selected.png");
	float interval = 0.0f;
	for (UI* MenuBar : MenuBarVec)
	{
		MenuBar->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.27f + interval });
		MenuBar->SetName("MenuBar");
		MenuBar->CreateImageRenderer(RenderOrder::UI);
		MenuBar->SetImg("MenuBar_Selected.png");
		MenuBar->SetTransform({ {0, 0}, {WinScale.X / 1.93f, WinScale.Y / 11.0f} });
		MenuBar->SetImg("MenuBar_UnSelected.png");
		MenuBar->SetTransform({ {0, 0}, {WinScale.X / 1.93f, WinScale.Y / 11.0f} });
		interval += WinScale.Y / 13.5f;
	}	

	IsSelectMenuInit = true;
}

void MainMenu::SelectMenuStart()
{
	if (false == IsSelectMenuInit)
	{
		SelectMenuInit();
	}

	Booper->RenderActiveOff();
	FocusMenuIndex = 0;
	MenuBarVec[0]->SetImg("MenuBar_Selected.png");	
	MenuBarVec[1]->SetImg("MenuBar_UnSelected.png");	
	MenuBarVec[2]->SetImg("MenuBar_UnSelected.png");	
}

void MainMenu::EnterChapter(float _DeltaTime)
{
	if (1 == SelectChapterNum)
	{
		// 씬 추가
	}

	// 장면 전환 추가

	// 수정 필요
	switch (SelectChapterNum)
	{
	case 1:
		GEngine->CreateLevel<Chapter1>("Chapter1");
		GEngine->ChangeLevel("Chapter1");
		break;
	}
	
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
	case EMainMenuState::SelectChapter:
		break;
	case EMainMenuState::EnterChapter:
		EnterChapter(_DeltaTime);
		break;
	case EMainMenuState::Exit:
		Exit(_DeltaTime);
		break;
	}
}

void MainMenu::StateChange(EMainMenuState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMainMenuState::Begin:
			break;
		case EMainMenuState::Enter:
			EnterStart();
			break;
		case EMainMenuState::SelectMenu:
			SelectMenuStart();
			break;
		case EMainMenuState::SelectChapter:
			break;
		case EMainMenuState::EnterChapter:
			break;
		case EMainMenuState::Exit:
			break;
		}
	}

	State = _State;
}

void MainMenu::LevelEnd(ULevel* _NextLevel)
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
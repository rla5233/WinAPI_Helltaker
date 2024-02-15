#include "MainMenu.h"

#include "BackGround.h"
#include "Dialogue.h"
#include "Character.h"
#include "Scene.h"
#include "UI.h"
#include "Chapter1.h"

#include <string>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageRenderer.h>

#include <wingdi.h>

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
	ContentsHelper::LoadImg("Scene\\Dialogue", "MainMenuDialogue_001.png");
	ContentsHelper::LoadImg("Scene\\Characters", "Beel_Fly.png");
	ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_001.png");
	ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_002.png");
	ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_003.png");
	ContentsHelper::LoadImg("UI", "MenuBar_UnSelected.png");
	ContentsHelper::LoadImg("UI", "MenuBar_Selected.png");
	ContentsHelper::LoadFolder("UI", "Booper");
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* BG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	BG->CreateBackGround("DefaultBG");
	AllActors.push_back(BG);

	Dialogue = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	Dialogue->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.45f });
	Dialogue->SetName("MainMenuDialogue_001");
	Dialogue->CreateImageRenderer(RenderOrder::Scene);
	Dialogue->GetRenderer()->SetImage(Dialogue->GetName() + ".png");
	Dialogue->GetRenderer()->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 2.0f } });
	AllActors.push_back(Dialogue);

	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.15f });
	Booper->SetName("Booper");
	Booper->CreateImageRenderer(RenderOrder::UI);
	Booper->GetImageRenderer()->SetImage(Booper->GetName());
	Booper->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X / 36.0f, WinScale.Y / 45.0f } });
	Booper->GetImageRenderer()->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->GetImageRenderer()->ChangeAnimation("Booper_Idle");
	Booper->CreateTextRenderer(RenderOrder::Text);
	Booper->GetTextRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.085f) }, { 0, 0 } });
	Booper->GetTextRenderer()->SetFont("Amiri");
	Booper->GetTextRenderer()->SetTextSize(22);
	Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));

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
	Booper->GetTextRenderer()->SetText("You find yourself surrounded by the void.\nPress [ENTER or A] to continue.");

	if (UEngineInput::IsPress(VK_SPACE) || UEngineInput::IsPress(VK_RETURN))
	{
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::BeginStart()
{}

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
	FVector WinScale = ContentsHelper::GetWindowScale();

	Beel = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Beel->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.9f });
	Beel->SetName("Beel_Fly");
	Beel->CreateImageRenderer(RenderOrder::Character);
	Beel->CreateNameRenderer(RenderOrder::Text);
	AllActors.push_back(Beel);

	Beel->GetImageRenderer()->SetImage(Beel->GetName() + ".png");
	Beel->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 1.44f} });
	Beel->GetNameRenderer()->SetText("Name");
	Beel->GetNameRenderer()->SetTextSize(23);
	Beel->GetNameRenderer()->SetTransform({ {0.0f, WinScale.Y * (0.36f)},{0,0}});
	Beel->GetNameRenderer()->SetTextColor(Color8Bit(255, 0, 0, 0));
}

void MainMenu::SelectMenu(float _DeltaTime)
{
	if (UEngineInput::IsDown('W') || UEngineInput::IsDown(VK_UP))
	{
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(Color8Bit(125, 125, 125, 0));
		SetFocusMenuIndex(FocusMenuIndex - 1);
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	}
	else if (UEngineInput::IsDown('S') || UEngineInput::IsDown(VK_DOWN))
	{
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(Color8Bit(125, 125, 125, 0));
		SetFocusMenuIndex(FocusMenuIndex + 1);
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		switch (FocusMenuIndex)
		{
		case 0:
			StateChange(EMainMenuState::CutScene);
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
	MenuBarVec.reserve(MenuBarCount);
	for (int i = 0; i < MenuBarCount; i++)
	{
		MenuBarVec.push_back(SpawnActor<UI>(static_cast<int>(UpdateOrder::UI)));
	}

	float interval = 0.0f;
   	FVector WinScale = ContentsHelper::GetWindowScale();
	
	for (UI* MenuBar : MenuBarVec)
	{
		MenuBar->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.27f + interval });
		MenuBar->SetName("MenuBar");
		MenuBar->CreateImageRenderer(RenderOrder::UI);
		MenuBar->GetImageRenderer()->SetTransform({ {0, 0}, {WinScale.X / 1.93f, WinScale.Y / 11.0f} });
		MenuBar->CreateTextRenderer(RenderOrder::Text);
		MenuBar->GetTextRenderer()->SetTransform({ {0, 2}, {0, 0} });
		MenuBar->GetTextRenderer()->SetFont("Amiri");
		MenuBar->GetTextRenderer()->SetTextSize(20);
		interval += WinScale.Y / 13.5f;
	}	

	IsSelectMenuInit = true;
}

void MainMenu::SelectMenuStart()
{
	Booper->GetImageRenderer()->ActiveOff();
	Booper->GetTextRenderer()->ActiveOff();

	if (false == IsSelectMenuInit)
	{
		SelectMenuInit();
	}

	SetFocusMenuIndex(0);
	std::vector<std::string> MenuBarText = { "NEW GAME", "CHAPTER SELECT", "EXIT" };
	for (int i = 0; i < MenuBarCount; i++)
	{
		if (i == FocusMenuIndex)
		{
			MenuBarVec[i]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
			MenuBarVec[i]->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
		}
		else
		{
			MenuBarVec[i]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
			MenuBarVec[i]->GetTextRenderer()->SetTextColor(Color8Bit(125, 125, 125, 0));
		}

		MenuBarVec[i]->GetTextRenderer()->SetText(MenuBarText[i]);
	}
}

void MainMenu::CutScene(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		++SceneIndex;
		SceneInput = true;
	}
	
	if (true == SceneInput)
	{
		FVector WinScale = ContentsHelper::GetWindowScale();

		switch (SceneIndex)
		{
		case 0:

			break;
		case 1:
			Dialogue->GetRenderer()->ActiveOff();
			Beel->GetImageRenderer()->ActiveOff();
			break;
		case 2:
			SceneActor->CreateImageRenderer(RenderOrder::Scene);
			SceneActor->GetRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.67f, WinScale.Y * 0.6f } });
			SceneActor->GetRenderer()->SetImage("CutScene1_001.png");
			break;
		case 3:
			SceneActor->GetRenderer()->SetImage("CutScene1_002.png");
			break;
		case 4:
			SceneActor->GetRenderer()->SetImage("CutScene1_003.png");
			break;
		case 5:
			StateChange(EMainMenuState::EnterChapter);
			break;
		}

		SceneInput = false;
	}
}

void MainMenu::CutSceneStart()
{
	for (UI* MenuBar : MenuBarVec)
	{
		MenuBar->GetImageRenderer()->ActiveOff();
	}

	Booper->GetImageRenderer()->ActiveOn();
	SelectChapterNum = 1;

	FVector WinScale = ContentsHelper::GetWindowScale();
	SceneActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	SceneActor->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.385f });
	AllActors.push_back(SceneActor);
}

void MainMenu::EnterChapter(float _DeltaTime)
{
	switch (SelectChapterNum)
	{
	case 1:
		GEngine->CreateLevel<Chapter1>("Chapter1");
		GEngine->ChangeLevel("Chapter1");
		break;
	}
}

void MainMenu::EnterChapterStart()
{
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
	case EMainMenuState::CutScene:
		CutScene(_DeltaTime);
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
		case EMainMenuState::CutScene:
			CutSceneStart();
			break;
		case EMainMenuState::EnterChapter:
			EnterChapterStart();
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
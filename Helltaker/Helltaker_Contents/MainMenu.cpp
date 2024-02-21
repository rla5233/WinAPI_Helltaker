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

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}
// 수정 (리팩토링 가능?)
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
	ContentsHelper::LoadFolder("Scene", "Transition");
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* BG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	BG->CreateBackGround("DefaultBG");
	AllActors.push_back(BG);

	CreateTransition();
	SpawnDialogue();
	SpawnBooper();	

	StateChange(EMainMenuState::Begin);
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

void MainMenu::CreateTransition()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	TransitionActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Transition));
	TransitionActor->SetName("Transition");
	TransitionActor->CreateImageRenderer(RenderOrder::Transition);
	TransitionActor->SetActorLocation(WinScale.Half2D());
	TransitionActor->GetImageRenderer()->SetTransform({ { 0, 0 }, WinScale });
	TransitionActor->GetImageRenderer()->SetImage("Transition");
	TransitionActor->GetImageRenderer()->CreateAnimation("Transition", "Transition", 0, 28, TransitionInter, false);
	TransitionActor->GetImageRenderer()->ActiveOff();
	AllActors.push_back(TransitionActor);
}

void MainMenu::SpawnDialogue()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	Dialogue->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.45f });
	Dialogue->SetName("MainMenuDialogue_001");
	Dialogue->CreateImageRenderer(RenderOrder::Scene);
	Dialogue->GetImageRenderer()->SetImage(Dialogue->GetName() + ".png");
	Dialogue->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y / 2.0f } });
	AllActors.push_back(Dialogue);
}

void MainMenu::SpawnBooper()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
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
	Booper->GetTextRenderer()->SetFont("맑은 고딕");
	Booper->GetTextRenderer()->SetTextSize(22);
	Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	Booper->GetTextRenderer()->SetText(" ");
	AllActors.push_back(Booper);
}

void MainMenu::Begin(float _DeltaTime)
{
	Booper->GetTextRenderer()->SetText("당신은 공허에 휩싸인 것을 느꼈다.\n계속 하려면 [ENTER]키를 누르시오.");

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
	Beel->GetNameRenderer()->SetText("위대한 파리 베엘제붑");
	Beel->GetNameRenderer()->SetFont("맑은 고딕");
	Beel->GetNameRenderer()->SetTextSize(23);
	Beel->GetNameRenderer()->SetTransform({ {0.0f, WinScale.Y * (0.36f)},{0,0}});
	Beel->GetNameRenderer()->SetTextColor(HELLTAKER_RED);

	Booper->GetTextRenderer()->SetText("반갑네 인간이여. 나를 괘념치 말게.\n그저 오랜 친구 베엘제붑일세.");
}

void MainMenu::SelectMenu(float _DeltaTime)
{
	if (UEngineInput::IsDown('W') || UEngineInput::IsDown(VK_UP))
	{
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex - 1);
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
	}
	else if (UEngineInput::IsDown('S') || UEngineInput::IsDown(VK_DOWN))
	{
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex + 1);
		MenuBarVec[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBarVec[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
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
		MenuBar->GetTextRenderer()->SetFont("맑은 고딕");
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
	std::vector<std::string> MenuBarText = { "새 게임", "챕터 선택", "나가기" };
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
			Booper->GetTextRenderer()->SetText("혹시 해설자가 필요하진 않은가?\n ");
			break;
		case 1:
			Dialogue->GetImageRenderer()->ActiveOff();
			Beel->GetImageRenderer()->ActiveOff();
			Beel->GetNameRenderer()->ActiveOff();
			Booper->GetTextRenderer()->SetText("허락해준다면 참 고맙겠어.\n ");
			break;
		case 2:
			SceneActor->CreateImageRenderer(RenderOrder::Scene);
			SceneActor->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.67f, WinScale.Y * 0.6f } });
			SceneActor->GetImageRenderer()->SetImage("CutScene1_001.png");
			Booper->GetTextRenderer()->SetText("어느날 당신은 악마들로 가득찬 하렘을\n꿈꾸고 일어났네.");
			break;
		case 3:
			SceneActor->GetImageRenderer()->SetImage("CutScene1_002.png");
			Booper->GetTextRenderer()->SetText("하지만 결코 이루기 쉽지 않은 꿈이지.\n어쩌면 네 목숨을 앗아갈지도 모르고.");
			break;
		case 4:
			SceneActor->GetImageRenderer()->SetImage("CutScene1_003.png");
			Booper->GetTextRenderer()->SetText("\"악마 하렘이 달렸다면, 그 어떤 대가도 싸지.\"\n그리하여 당신은 지옥으로 모험을 떠났네.");
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
		MenuBar->GetTextRenderer()->ActiveOff();
	}

	Booper->GetImageRenderer()->ActiveOn();
	Booper->GetTextRenderer()->ActiveOn();
	Booper->GetTextRenderer()->SetText("또 헬테이커의 이야기를 들려달라고? 재미있군...\n ");
	SelectChapterNum = 1;

	FVector WinScale = ContentsHelper::GetWindowScale();
	SceneActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	SceneActor->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.385f });
	AllActors.push_back(SceneActor);
}

void MainMenu::EnterChapter(float _DeltaTime)
{
	if (19 == TransitionActor->GetImageRenderer()->GetCurAnimationFrame())
	{
		switch (SelectChapterNum)
		{
		case 1:
			GEngine->CreateLevel<Chapter1>("Chapter1");
			GEngine->ChangeLevel("Chapter1");
			break;
		}		
	}
}

void MainMenu::EnterChapterStart()
{
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition");
}

void MainMenu::Exit(float _DeltaTime)
{}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

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
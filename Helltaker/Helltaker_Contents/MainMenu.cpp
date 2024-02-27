#include "MainMenu.h"

#include "Character.h"
#include "Scene.h"
#include "Chapter1.h"

bool MainMenu::IsLoad = false;

const std::vector<const char*> MainMenu::MainMenu_Script
{
	/* 0  Demon	   */ "위대한 파리 베엘제붑",
	/* 1  Script 1 */ "당신은 공허에 휩싸인 것을 느꼈다.\n계속 하려면 [ENTER]키를 누르시오.",
	/* 2  Script 2 */ "반갑네 인간이여. 나를 괘념치 말게.\n그저 오랜 친구 베엘제붑일세.",
	/* 3  MenuBar1 */ "새 게임",
	/* 4  MenuBar2 */ "챕터 선택",
	/* 5  MenuBar3 */ "나가기",
	/* 6  NewGame1 */ "또 헬테이커의 이야기를 들려달라고? 재미있군...",
	/* 7  NewGame2 */ "혹시 해설자가 필요하진 않은가?",
	/* 8  NewGame3 */ "허락해준다면 참 고맙겠어.",
	/* 9  NewGame4 */ "어느날 당신은 악마들로 가득찬 하렘을\n꿈꾸고 일어났네.",
	/* 10 NewGame5 */ "하지만 결코 이루기 쉽지 않은 꿈이지.\n어쩌면 네 목숨을 앗아갈지도 모르고.",
	/* 11 NewGame6 */ "\"악마 하렘이 달렸다면, 그 어떤 대가도 싸지.\"\n그리하여 당신은 지옥으로 모험을 떠났네.",
	/* 12 Exit     */ "나도 수 없이 시도 해봤지만 아직 제대로 성공한 적이 없지."
};

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

// 수정 (리팩토링 가능?)
void MainMenu::BeginPlay()
{
	CutSceneManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialogue", "MainMenuDialogue_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Beel_Fly.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_001.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_002.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene1_003.png");

		IsLoad = true;
	}
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	CutSceneManager::LevelStart(_PrevLevel);

	C_CreateSceneBG();
	C_SpawnDialogue("MainMenuDialogue_001.png");
	C_SpawnBooper();	
	CreateTransition();

	StateChange(EMainMenuState::Begin);
}

void MainMenu::Begin()
{
	if (UEngineInput::IsPress(VK_SPACE) || UEngineInput::IsPress(VK_RETURN))
	{
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::BeginStart()
{
	C_BooperTextSet(MainMenu_Script[1]);
}

void MainMenu::Enter()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		StateChange(EMainMenuState::Select);
	}
}

void MainMenu::EnterStart()
{
	C_SpawnCharacter("Beel", "Beel_Fly.png", MainMenu_Script[0]);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.995f, WinScale.Y * 0.693f };
	C_CharacterSetTransform({ {0, 0}, Scale });
	C_BooperTextSet(MainMenu_Script[2]);
}

void MainMenu::Select()
{
	FocusMenuBarCheck();
}

void MainMenu::SelectStart()
{
	C_BooperImageRendererOff();
	C_BooperTextSet(" ");

	C_SpawnMenubar({ 0.5f, 0.79f }, 3);
	C_MenubarTextSet(0, MainMenu_Script[3]);
	C_MenubarTextSet(1, MainMenu_Script[4]);
	C_MenubarTextSet(2, MainMenu_Script[5]);
}

void MainMenu::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		StateChange(EMainMenuState::NewGame);
		break;
	case 1:
		StateChange(EMainMenuState::None);
		break;
	case 2:
		StateChange(EMainMenuState::Exit);
		break;
	}
}

void MainMenu::NewGame()
{
	switch (NewGameOrder)
	{
	case 0:
		NewGameOrder1();
		break;
	case 1:
		NewGameOrder2();
		break;
	case 2:
	case 3:
	case 4:
		NewGameLastOrder();
		break;
	case 5:
		if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		{
			StateChange(EMainMenuState::EnterChapter);
		}
		break;
	}
}

void MainMenu::NewGameOrder1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(MainMenu_Script[7]);
		++NewGameOrder;
	}
}

void MainMenu::NewGameOrder2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetDialogue()->AllRenderersActiveOff();
		C_GetSceneCharacter()->AllRenderersActiveOff();
		C_BooperTextSet(MainMenu_Script[8]);
		++NewGameOrder;
	}
}

void MainMenu::NewGameLastOrder()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { WinScale.X * 0.67f, WinScale.Y * 0.6f };
		std::string ImgName = "CutScene1_00";
		ImgName += std::to_string(NewGameOrder - 1) + ".png";
		C_ChangeDialogue(ImgName, { { 0, 0 }, Scale });
		C_BooperTextSet(MainMenu_Script[NewGameOrder + 7]);
		SelectChapterNum = 1;
		++NewGameOrder;
	}
}

void MainMenu::NewGameStart()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(MainMenu_Script[6]);
	NewGameOrder = 0;
}

void MainMenu::EnterChapter()
{
	if (19 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
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
	TransitionOn();
}

void MainMenu::Exit()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->MainWindow.Off();;
	}
}

void MainMenu::ExitStart()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(MainMenu_Script[12]);
}

void MainMenu::Tick(float _DeltaTime)
{
	CutSceneManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void MainMenu::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMainMenuState::Begin:
		Begin();
		break;
	case EMainMenuState::Enter:
		Enter();
		break;
	case EMainMenuState::Select:
		Select();
		break;
	case EMainMenuState::NewGame:
		NewGame();
		break;
	case EMainMenuState::EnterChapter:
		EnterChapter();
		break;
	case EMainMenuState::Exit:
		Exit();
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
			BeginStart();
			break;
		case EMainMenuState::Enter:
			EnterStart();
			break;
		case EMainMenuState::Select:
			SelectStart();
			break;
		case EMainMenuState::NewGame:
			NewGameStart();
			break;
		case EMainMenuState::EnterChapter:
			EnterChapterStart();
			break;
		case EMainMenuState::Exit:
			ExitStart();
			break;
		}
	}

	State = _State;
}

void MainMenu::LevelEnd(ULevel* _NextLevel)
{
	CutSceneManager::LevelEnd(_NextLevel);
}
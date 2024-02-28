#include "MainMenu.h"

#include "Chapter1.h"
#include "Character.h"
#include "Scene.h"
#include "UI.h"

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
		
		ContentsHelper::LoadImg("UI", "ChapterSelect_Bottom.png");
		ContentsHelper::LoadImg("UI", "ChapterSelect_Top.png");
		ContentsHelper::LoadImg("UI", "UnSelect_001.png");
		ContentsHelper::LoadImg("UI", "UnSelect_002.png");
		ContentsHelper::LoadImg("UI", "UnSelect_003.png");
		ContentsHelper::LoadImg("UI", "UnSelect_004.png");
		ContentsHelper::LoadImg("UI", "UnSelect_005.png");
		ContentsHelper::LoadImg("UI", "UnSelect_006.png");
		ContentsHelper::LoadImg("UI", "UnSelect_007.png");
		ContentsHelper::LoadImg("UI", "UnSelect_008.png");
		ContentsHelper::LoadImg("UI", "UnSelect_009.png");
		ContentsHelper::LoadImg("UI", "UnSelect_010.png");
		ContentsHelper::LoadImg("UI", "Select_001.png");
		ContentsHelper::LoadImg("UI", "Select_002.png");
		ContentsHelper::LoadImg("UI", "Select_003.png");
		ContentsHelper::LoadImg("UI", "Select_004.png");
		ContentsHelper::LoadImg("UI", "Select_005.png");
		ContentsHelper::LoadImg("UI", "Select_006.png");
		ContentsHelper::LoadImg("UI", "Select_007.png");
		ContentsHelper::LoadImg("UI", "Select_008.png");
		ContentsHelper::LoadImg("UI", "Select_009.png");
		ContentsHelper::LoadImg("UI", "Select_010.png");

		IsLoad = true;
	}
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	CutSceneManager::LevelStart(_PrevLevel);

	C_CreateSceneBG();
	C_SpawnDialogue("MainMenuDialogue_001.png");

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector ImgScale = C_GetDialogue()->GetImageRenderer()->GetImage()->GetScale();
	FVector Scale = { ImgScale.X * WinScale.X / 1920.0f, WinScale.Y * 0.5045f };
	FVector Pos = { (Scale.X - WinScale.X) * (-0.5f), 0.0f};
	C_GetDialogue()->GetImageRenderer()->SetTransform({ Pos, Scale });
	
	C_SpawnBooper();	
	CreateTransition();

	StateChange(EMainMenuState::Begin);
}

void MainMenu::Begin(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	if (UEngineInput::IsPress(VK_SPACE) || UEngineInput::IsPress(VK_RETURN))
	{
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::BeginStart()
{
	C_BooperTextSet(MainMenu_Script[1]);
}

void MainMenu::Enter(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		StateChange(EMainMenuState::Select);
	}
}

void MainMenu::EnterStart()
{
	C_SpawnCharacter("Beel", "Beel_Fly.png", MainMenu_Script[0]);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 1.04f, WinScale.Y * 0.693f };
	FVector Pos = { 0.0f, WinScale.Y * (-0.0445f) };
	C_CharacterSetTransform({ Pos, Scale });
	C_BooperTextSet(MainMenu_Script[2]);
}

void MainMenu::Select(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	FocusMenuBarCheck();
}

void MainMenu::SelectStart()
{
	C_BooperImageRendererOff();
	C_BooperTextSet(" ");

	C_SpawnMenubar({ 0.5f, 0.786f }, 3);
	C_MenubarTextSet(0, MainMenu_Script[3]);
	C_MenubarTextSet(1, MainMenu_Script[4]);
	C_MenubarTextSet(2, MainMenu_Script[5]);
	
	SpawnSC_MenuBar(10);
}

void MainMenu::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		StateChange(EMainMenuState::NewGame);
		break;
	case 1:
		StateChange(EMainMenuState::SelectChapter);
		break;
	case 2:
		StateChange(EMainMenuState::Exit);
		break;
	}
}

void MainMenu::NewGame(float _DeltaTime)
{
	switch (NewGameOrder)
	{
	case 0:
		DialogueMoveUpdate(_DeltaTime);
		NewGameOrder1();
		break;
	case 1:
		DialogueMoveUpdate(_DeltaTime);
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
		FVector Pos = { 0.0f, WinScale.Y * (-0.02f) };
		std::string ImgName = "CutScene1_00";
		ImgName += std::to_string(NewGameOrder - 1) + ".png";
		C_ChangeDialogue(ImgName, { Pos, Scale });

		C_BooperTextSet(MainMenu_Script[NewGameOrder + 7]);
		Pos = { 0.0f, WinScale.Y * (-0.0995f) };
		C_BooperSetTextPosition(Pos);
		SelectChapterNum = 1;
		++NewGameOrder;
	}
}

void MainMenu::NewGameStart()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(MainMenu_Script[6]);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { 0.0f, WinScale.Y * (-0.12f) };
	C_BooperSetTextPosition(Pos);
	NewGameOrder = 0;
}

void MainMenu::SelectChapter(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	
	FocusSC_MenuBarCheck();

	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		ReturnSelect();
	}
}

void MainMenu::SelectChapterStart()
{
	C_MenubarRenderActiveOff();
	C_GetSceneCharacter()->GetNameRenderer()->ActiveOff();

	SC_MenuBarOn();
}

void MainMenu::SpawnSC_MenuBar(int _IndexCount)
{
	float interval = 0.0f;
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { WinScale.X * 0.218f, WinScale.Y * 0.75f };
	FVector Scale = { WinScale.X * 0.0573f, WinScale.Y * 0.07f };

	SC_MenuCount = _IndexCount;
	SelectChapterMenu.reserve(SC_MenuCount + 2);
	for (int i = 0; i < SC_MenuCount; i++)
	{
		UI* MenuBar = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
		MenuBar->SetName("SelectChapterMenuBar");
		MenuBar->SetActorLocation({ Pos.X + interval, Pos.Y });

		MenuBar->CreateImageRenderer(RenderOrder::UI);

		if (i == 0)
		{
			MenuBar->GetImageRenderer()->SetImage("Select_001.png");
		}
		else
		{
			std::string Name = "UnSelect_0";
			std::string Num = std::to_string(i + 1);
			if (1 == Num.size())
			{
				Name += "0";
			}
			Name += Num + ".png";
			MenuBar->GetImageRenderer()->SetImage(Name);
		}
		
		MenuBar->GetImageRenderer()->SetTransform({ { 0, 0 }, Scale });
		MenuBar->AllRenderersActiveOff();
		
		interval += WinScale.X * 0.0625f;
		SelectChapterMenu.push_back(MenuBar);
	}

	for (int i = 0; i < 2; i++)
	{
		UI* TopBottomBar = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
		TopBottomBar->SetName("SelectChapterTopBottomBar");
		TopBottomBar->CreateImageRenderer(RenderOrder::UI);
		TopBottomBar->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.749f, WinScale.Y * 0.05f } });
		TopBottomBar->GetImageRenderer()->ActiveOff();

		if (i == 0)
		{
			TopBottomBar->SetActorLocation({ WinScale.hX(), Pos.Y + WinScale.Y * 0.05f });
			TopBottomBar->GetImageRenderer()->SetImage("ChapterSelect_Bottom.png");
		}
		else
		{
			TopBottomBar->SetActorLocation({ WinScale.hX(), Pos.Y - WinScale.Y * 0.05f });
			TopBottomBar->GetImageRenderer()->SetImage("ChapterSelect_Top.png");
		}

		SelectChapterMenu.push_back(TopBottomBar);
	}

	SetFocusSC_MenuIndex(0);
}

void MainMenu::SC_MenuBarOn()
{
	for (UI* Menu : SelectChapterMenu)
	{
		if (nullptr == Menu)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Menu->AllRenderersActiveOn();
	}
}

void MainMenu::SC_MenuBarOff()
{
	for (UI* Menu : SelectChapterMenu)
	{
		if (nullptr == Menu)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Menu->AllRenderersActiveOff();
	}
}

void MainMenu::FocusSC_MenuBarCheck()
{
	if (UEngineInput::IsDown('A') || UEngineInput::IsDown(VK_LEFT))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		SelectChapterMenu[FocusSC_MenuIndex]->GetImageRenderer()->SetImage("UnSelect_001.png");
		SetFocusSC_MenuIndex(FocusSC_MenuIndex - 1);
		SelectChapterMenu[FocusSC_MenuIndex]->GetImageRenderer()->SetImage("Select_001.png");
	}
	else if (UEngineInput::IsDown('D') || UEngineInput::IsDown(VK_RIGHT))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		SelectChapterMenu[FocusSC_MenuIndex]->GetImageRenderer()->SetImage("UnSelect_001.png");
		SetFocusSC_MenuIndex(FocusSC_MenuIndex + 1);
		SelectChapterMenu[FocusSC_MenuIndex]->GetImageRenderer()->SetImage("Select_001.png");
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		//SelectMenu();	
	}
}

void MainMenu::SetFocusSC_MenuIndex(int _Index)
{
	FocusSC_MenuIndex = _Index;

	if (FocusSC_MenuIndex < 0)
	{
		FocusSC_MenuIndex = SC_MenuCount - 1;
	}

	if (FocusSC_MenuIndex >= SC_MenuCount)
	{
		FocusSC_MenuIndex = 0;
	}
}

void MainMenu::ReturnSelect()
{
	SC_MenuBarOff();
	C_MenubarRenderActiveOn();
	C_GetSceneCharacter()->GetNameRenderer()->ActiveOn();
	State = EMainMenuState::Select;
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

void MainMenu::Exit(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
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

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { 0.0f, WinScale.Y * (-0.12f) };
	C_BooperSetTextPosition(Pos);
}

void MainMenu::DialogueMoveUpdate(float _DeltaTime)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = C_GetDialogue()->GetImageRenderer()->GetPosition();
	float Diff = WinScale.X * _DeltaTime * 0.04f;
	CurPos += { Diff, 0.0f };
	DialogueMoveSum += Diff;
	C_GetDialogue()->GetImageRenderer()->SetPosition(CurPos);

	FVector ImgScale = C_GetDialogue()->GetImageRenderer()->GetImage()->GetScale();
	float DialogueMoveDistance = (ImgScale.X * WinScale.X / 1920.0f) * 0.5f;
	if (DialogueMoveDistance <= DialogueMoveSum)
	{
		FVector Scale = { ImgScale.X * WinScale.X / 1920.0f, WinScale.Y * 0.5045f };
		FVector Pos = { (Scale.X - WinScale.X) * (-0.5f), 0.0f };
		C_GetDialogue()->GetImageRenderer()->SetTransform({ Pos, Scale });
		DialogueMoveSum = 0.0f;
	}
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
		Begin(_DeltaTime);
		break;
	case EMainMenuState::Enter:
		Enter(_DeltaTime);
		break;
	case EMainMenuState::Select:
		Select(_DeltaTime);
		break;
	case EMainMenuState::SelectChapter:
		SelectChapter(_DeltaTime);
		break;
	case EMainMenuState::NewGame:
		NewGame(_DeltaTime);
		break;
	case EMainMenuState::EnterChapter:
		EnterChapter();
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
			BeginStart();
			break;
		case EMainMenuState::Enter:
			EnterStart();
			break;
		case EMainMenuState::Select:
			SelectStart();
			break;
		case EMainMenuState::SelectChapter:
			SelectChapterStart();
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
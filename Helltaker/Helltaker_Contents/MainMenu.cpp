﻿#include "MainMenu.h"

#include "Character.h"
#include "Scene.h"
#include "UI.h"

#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"
#include "Chapter5.h"
#include "Chapter6.h"
#include "Chapter7.h"
#include "Chapter8.h"
#include "Chapter9.h"
#include "EpilogueOpening.h"

bool MainMenu::IsLoad = false;
bool MainMenu::ReturnMainMenu = false;

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
	/* 12 Exit     */ "나도 수 없이 시도 해봤지만 아직 제대로 성공한 적이 없지.",
	/* 13 Return   */ "다른 원하는 것이라도 있나?",
	/* 14 Chap1    */ "Chapter 1 - 피곤한 악마",
	/* 15 Chap2    */ "Chapter 2 - 음란한 악마",
	/* 16 Chap3    */ "Chapter 3 - 세 쌍둥이 악마",
	/* 17 Chap4    */ "Chapter 4 - 시큰둥한 악마",
	/* 18 Chap5    */ "Chapter 5 - 상스러운 악마",
	/* 19 Chap6    */ "Chapter 6 - 호기심 많은 천사",
	/* 20 Chap7    */ "Chapter 7 - 끝내주는 악마 저스티스",
	/* 21 Chap8    */ "Chapter 8 - 지옥의 CEO",
	/* 22 Chap9    */ "Chapter 9 - 저지먼트",
	/* 23 Chap10   */ "Chapter 10 - 에필로그"
};

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::BeginPlay()
{
	HellTakerManager::BeginPlay();

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

		ContentsHelper::LoadSound("Sound\\BGM", "Apropos.wav");
		
		ContentsHelper::LoadSound("Sound\\Effect", "menu_button_focus.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "menu_button_confirm.wav");

		IsLoad = true;
	}

	MainMenuBGMPlayer = UEngineSound::SoundPlay("Apropos.wav");
	MainMenuBGMPlayer.Loop();
	MainMenuBGMPlayer.Off();
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	C_CreateSceneBG();
	C_SpawnDialogue("MainMenuDialogue_001.png");

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector ImgScale = C_GetDialogue()->GetImageRenderer()->GetImage()->GetScale();
	FVector Scale = { ImgScale.X * WinScale.X / 1920.0f, WinScale.Y * 0.5045f };
	FVector Pos = { (Scale.X - WinScale.X) * (-0.5f), 0.0f};
	C_GetDialogue()->GetImageRenderer()->SetTransform({ Pos, Scale });
	
	C_SpawnBooper();	

	MainMenuBGMPlayer.On();

	if (false == ReturnMainMenu)
	{
		StateChange(EMainMenuState::Begin);
	}
	else
	{
		StateChange(EMainMenuState::Return);
	}
}

void MainMenu::BeginStart()
{
	C_BooperTextSet(MainMenu_Script[1]);
	ReturnMainMenu = true;
}

void MainMenu::Begin(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	if (UEngineInput::IsPress(VK_SPACE) || UEngineInput::IsPress(VK_RETURN))
	{
		UEngineSound::SoundPlay("booper_click.wav");
		StateChange(EMainMenuState::Enter);
	}
}

void MainMenu::EnterStart()
{
	FVector Scale = { 1.04f, 0.693f };
	FVector Pos = { 0.0f, -0.0445f };
	C_SpawnCharacter("Beel", "Beel_Fly.png", MainMenu_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(MainMenu_Script[2]);
}

void MainMenu::Enter(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);

	if ((false == C_GetSceneCharacter()->IsImgMoveOn())	
	&& (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN)))
	{
		UEngineSound::SoundPlay("booper_click.wav");
		StateChange(EMainMenuState::Select);
	}
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

void MainMenu::Select(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	if (true == FocusMenuBarCheck())
	{
		UEngineSound::SoundPlay("menu_button_focus.wav");
	}
}

void MainMenu::SelectMenu()
{
	UEngineSound::SoundPlay("menu_button_confirm.wav");
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

void MainMenu::NewGameStart()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(MainMenu_Script[6]);

	OrderCount = 0;
}

void MainMenu::NewGame(float _DeltaTime)
{
	switch (OrderCount)
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
			UEngineSound::SoundPlay("booper_click.wav");
			StateChange(EMainMenuState::EnterChapter);
		}
		break;
	}
}

void MainMenu::NewGameOrder1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(MainMenu_Script[7], true);
		++OrderCount;
	}
}

void MainMenu::NewGameOrder2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetDialogue()->AllRenderersActiveOff();
		C_GetSceneCharacter()->AllRenderersActiveOff();
		C_BooperTextSet(MainMenu_Script[8], true);
		++OrderCount;
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
		ImgName += std::to_string(OrderCount - 1) + ".png";
		C_ChangeDialogue(ImgName, { Pos, Scale });

		C_BooperTextSet(MainMenu_Script[OrderCount + 7], true);
		SelectChapterNum = 1;
		++OrderCount;
	}
}

void MainMenu::SelectChapterStart()
{
	C_MenubarRenderActiveOff();
	C_GetSceneCharacter()->GetNameRenderer()->ActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = 0.04f;
	C_BooperTextSet(MainMenu_Script[14]);
	C_GetBooper()->GetTextRenderer()->SetPosition({ 0.0f, WinScale.Y * PosY });

	SC_MenuBarOn();
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

void MainMenu::SpawnSC_MenuBar(int _IndexCount)
{
	float interval = 0.0f;
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { WinScale.X * 0.218f, WinScale.Y * 0.801f };
	FVector Scale = { WinScale.X * 0.0573f, WinScale.Y * 0.07f };

	SC_MenuCount = _IndexCount;
	SC_MenuBar.reserve(SC_MenuCount + 2);
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
		SC_MenuBar.push_back(MenuBar);
		C_AddCutSceneActor(MenuBar);
	}

	for (int i = 0; i < 2; i++)
	{
		UI* TopBottomBar = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
		TopBottomBar->SetName("SC_TopBottomBar");
		TopBottomBar->CreateImageRenderer(RenderOrder::UI);
		TopBottomBar->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.749f, WinScale.Y * 0.05f } });
		TopBottomBar->GetImageRenderer()->ActiveOff();

		if (i == 0)
		{
			TopBottomBar->SetActorLocation({ WinScale.hX(), Pos.Y + WinScale.Y * 0.0545f });
			TopBottomBar->GetImageRenderer()->SetImage("ChapterSelect_Bottom.png");
		}
		else
		{
			TopBottomBar->SetActorLocation({ WinScale.hX(), Pos.Y - WinScale.Y * 0.0545f });
			TopBottomBar->GetImageRenderer()->SetImage("ChapterSelect_Top.png");
		}

		SC_MenuBar.push_back(TopBottomBar);
		C_AddCutSceneActor(TopBottomBar);
	}

	SetFocusSC_MenuIndex(0);
}

void MainMenu::SelectChapterMenu()
{
	SelectChapterNum = FocusSC_MenuIndex + 1;

	if (1 == SelectChapterNum)
	{
		C_GetSceneCharacter()->GetNameRenderer()->ActiveOn();
		StateChange(EMainMenuState::NewGame);
	}
	else
	{
		StateChange(EMainMenuState::EnterChapter);
	}
}

void MainMenu::SC_MenuBarOn()
{
	for (int i = 0; i < static_cast<int>(SC_MenuBar.size()); i++)
	{
		if (nullptr == SC_MenuBar[i])
		{
			MsgBoxAssert("Actor is nullptr");
		}

		SetFocusSC_MenuIndex(i);

		if (0 == i)
		{
			AutoSC_SelectMenuImage();
		}
		else if (i < 10)
		{
			AutoSC_UnSelectMenuImage();
		}

		SC_MenuBar[i]->AllRenderersActiveOn();
	}

	SetFocusSC_MenuIndex(0);
}

void MainMenu::SC_MenuBarOff()
{
	for (UI* Menu : SC_MenuBar)
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
		AutoSC_UnSelectMenuImage();
		SetFocusSC_MenuIndex(FocusSC_MenuIndex - 1);
		AutoSC_SelectMenuImage();
		C_GetBooper()->GetTextRenderer()->SetText(MainMenu_Script[14 + FocusSC_MenuIndex]);
		UEngineSound::SoundPlay("menu_button_focus.wav");
	}
	else if (UEngineInput::IsDown('D') || UEngineInput::IsDown(VK_RIGHT))
	{
		AutoSC_UnSelectMenuImage();
		SetFocusSC_MenuIndex(FocusSC_MenuIndex + 1);
		AutoSC_SelectMenuImage();
		C_GetBooper()->GetTextRenderer()->SetText(MainMenu_Script[14 + FocusSC_MenuIndex]);
		UEngineSound::SoundPlay("menu_button_focus.wav");
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		SC_MenuBarOff();
		SelectChapterMenu();
	}
}

void MainMenu::AutoSC_SelectMenuImage()
{
	std::string Name = "Select_0";
	std::string Num = std::to_string(FocusSC_MenuIndex + 1);
	if (1 == Num.size())
	{
		Name += "0";
	}
	Name += Num + ".png";
	SC_MenuBar[FocusSC_MenuIndex]->GetImageRenderer()->SetImage(Name);
}

void MainMenu::AutoSC_UnSelectMenuImage()
{
	std::string Name = "UnSelect_0";
	std::string Num = std::to_string(FocusSC_MenuIndex + 1);
	if (1 == Num.size())
	{
		Name += "0";
	}
	Name += Num + ".png";
	SC_MenuBar[FocusSC_MenuIndex]->GetImageRenderer()->SetImage(Name);
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
	C_BooperTextSet(" ");
	C_MenubarRenderActiveOn();
	C_GetSceneCharacter()->GetNameRenderer()->ActiveOn();
	State = EMainMenuState::Select;
}

void MainMenu::EnterChapterStart()
{
	TransitionOn();
}

void MainMenu::EnterChapter()
{
	if (19 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
	{
		std::string Chapter = "Chapter";
		Chapter += std::to_string(SelectChapterNum);
		switch (SelectChapterNum)
		{
		case 1:
			CreateChapter<Chapter1>(Chapter);
			break;
		case 2:
			CreateChapter<Chapter2>(Chapter);
			break;
		case 3:
			CreateChapter<Chapter3>(Chapter);
			break;
		case 4:
			CreateChapter<Chapter4>(Chapter);
			break;
		case 5:
			CreateChapter<Chapter5>(Chapter);
			break;
		case 6:
			CreateChapter<Chapter6>(Chapter);
			break;
		case 7:
			CreateChapter<Chapter7>(Chapter);
			break;
		case 8:
			CreateChapter<Chapter8>(Chapter);
			break;
		case 9:
			CreateChapter<Chapter9>(Chapter);
			break;
		case 10:
			Chapter = "EpilogueOpening";
			CreateChapter<EpilogueOpening>(Chapter);
			break;
		}		

		GEngine->ChangeLevel(Chapter);
	}
}

void MainMenu::ReturnStart()
{
	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");
	MainMenuBGMPlayer.Replay();

	OrderCount = 0;
}

void MainMenu::Return(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	switch (OrderCount)
	{
	case 0:
		Return1();
		break;
	case 1:
		Return2();
		break;
	}
}

void MainMenu::Return1()
{
	if (false == SetReturn
	&&  26 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
	{
		FVector Scale = { 1.04f, 0.693f };
		FVector Pos = { 0.0f, -0.0445f };
		C_SpawnCharacter("Beel", "Beel_Fly.png", MainMenu_Script[0], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(MainMenu_Script[13]);

		SetReturn = true;
	}

	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
		SetReturn = true;
		++OrderCount;
	}
}

void MainMenu::Return2()
{
	if ((false == C_GetSceneCharacter()->IsImgMoveOn())
		&& (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN)))
	{
		UEngineSound::SoundPlay("booper_click.wav");
		StateChange(EMainMenuState::Select);
	}
}

void MainMenu::Exit(float _DeltaTime)
{
	DialogueMoveUpdate(_DeltaTime);
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->MainWindow.Off();
	}
}

void MainMenu::ExitStart()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(MainMenu_Script[12]);

	UEngineSound::SoundPlay("booper_click.wav");
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
	case EMainMenuState::Return:
		Return(_DeltaTime);
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
		case EMainMenuState::Return:
			ReturnStart();
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

	MainMenuBGMPlayer.Off();
	SC_MenuBar.clear();
}
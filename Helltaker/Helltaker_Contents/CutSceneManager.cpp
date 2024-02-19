#include "CutSceneManager.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Character.h"
#include "HitActor.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Thorn.h"
#include "Scene.h"
#include "Demon.h"
#include "Hero.h"
#include "Text.h"
#include "UI.h"

CutSceneManager::CutSceneManager()
{
}

CutSceneManager::~CutSceneManager()
{
}

void CutSceneManager::C_SpawnDialogue(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Scene* Dialogue = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	Dialogue->SetActorLocation({ WinScale.hX(), WinScale.Y / 2.45f });
	Dialogue->SetName("Dialogue");
	Dialogue->CreateImageRenderer(RenderOrder::Scene);
	Dialogue->GetImageRenderer()->SetImage(_Name);
	Dialogue->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y * 0.5045f } });
	AllCutSceneActors.push_back(Dialogue);
}

void CutSceneManager::C_SpawnCharacter(std::string_view _Name, std::string_view _ImgName, std::string_view _Text)
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	C_Character = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	C_Character->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	C_Character->SetName(_Name);
	C_Character->CreateImageRenderer(RenderOrder::Character);
	C_Character->CreateNameRenderer(RenderOrder::Text);
	AllCutSceneActors.push_back(C_Character);

	C_Character->GetImageRenderer()->SetImage(_ImgName);
	C_Character->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X * 0.255f, WinScale.Y * 0.611f} });

	C_Character->GetNameRenderer()->SetText(_Text);
	C_Character->GetNameRenderer()->SetFont("¸¼Àº °íµñ");
	C_Character->GetNameRenderer()->SetTextSize(40);
	C_Character->GetNameRenderer()->SetTransform({ { 0.0f, WinScale.Y * 0.317f }, { 0, 0 } });
	C_Character->GetNameRenderer()->SetTextColor(HELLTAKER_RED);
}

void CutSceneManager::C_SpawnBooper()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	C_Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	C_Booper->SetActorLocation({ WinScale.hX(), WinScale.Y / 1.15f });
	C_Booper->SetName("Booper");
	C_Booper->CreateImageRenderer(RenderOrder::UI);
	C_Booper->GetImageRenderer()->SetImage(C_Booper->GetName());
	C_Booper->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X / 36.0f, WinScale.Y / 45.0f } });
	C_Booper->GetImageRenderer()->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	C_Booper->GetImageRenderer()->ChangeAnimation("Booper_Idle");
	C_Booper->CreateTextRenderer(RenderOrder::Text);
	C_Booper->GetTextRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.0995f) }, { 0, 0 } });
	C_Booper->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
	C_Booper->GetTextRenderer()->SetTextSize(35);
	C_Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	C_Booper->GetTextRenderer()->SetText(" ");
	AllCutSceneActors.push_back(C_Booper);
}

void CutSceneManager::C_BooperTextSet(std::string_view _Text)
{
	C_Booper->GetTextRenderer()->SetText(_Text);
}

void CutSceneManager::C_SpawnMenubar()
{
	float interval = 0.0f;
	FVector WinScale = ContentsHelper::GetWindowScale();

	MenuBar.reserve(MenuBarCount);
	for (int i = 0; i < MenuBarCount; i++)
	{
		MenuBar.push_back(SpawnActor<UI>(static_cast<int>(UpdateOrder::UI)));

		MenuBar[i]->SetActorLocation({ WinScale.hX(), (WinScale.Y * 0.87f) + interval });
		MenuBar[i]->SetName("MenuBar");

		MenuBar[i]->CreateImageRenderer(RenderOrder::UI);
		MenuBar[i]->GetImageRenderer()->SetTransform({ {0, 0}, {WinScale.X * 0.518f, WinScale.Y * 0.091f} });

		MenuBar[i]->CreateTextRenderer(RenderOrder::Text);
		MenuBar[i]->GetTextRenderer()->SetTransform({ {0, -4}, {0, 0} });
		MenuBar[i]->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
		MenuBar[i]->GetTextRenderer()->SetTextSize(26);
		MenuBar[i]->GetTextRenderer()->SetText("Test");

		if (i == 0)
		{
			MenuBar[i]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
			MenuBar[i]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
		}
		else
		{
			MenuBar[i]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
			MenuBar[i]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		}

		interval += WinScale.Y * 0.074f;
		AllCutSceneActors.push_back(MenuBar[i]);
	}

	SetFocusMenuIndex(0);
}

void CutSceneManager::EnterChooseMenuCheck()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_Booper->GetImageRenderer()->ActiveOff();
		C_SpawnMenubar();

		Phase = ECutScenePhase::Enter;
	}
}

void CutSceneManager::SetFocusMenuIndex(int _Index)
{
	FocusMenuIndex = _Index;

	if (FocusMenuIndex < 0)
	{
		FocusMenuIndex = MenuBarCount - 1;
	}

	if (FocusMenuIndex >= MenuBarCount)
	{
		FocusMenuIndex = 0;
	}
}

void CutSceneManager::SelectMenuBar()
{
	if (UEngineInput::IsDown('W') || UEngineInput::IsDown(VK_UP))
	{
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex - 1);
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
	}
	else if (UEngineInput::IsDown('S') || UEngineInput::IsDown(VK_DOWN))
	{
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex + 1);
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{

	}
}

void CutSceneManager::CutSceneStart()
{
	ChapterManager::CutSceneStart();

	Phase = ECutScenePhase::Start;
}

void CutSceneManager::Tick(float _DeltaTime)
{
	ChapterManager::Tick(_DeltaTime);

	PhaseUpdate(_DeltaTime);
}

void CutSceneManager::PhaseUpdate(float _DeltaTime)
{
	switch (Phase)
	{
	case ECutScenePhase::Start:
		EnterChooseMenuCheck();
		break;
	case ECutScenePhase::Enter:
		SelectMenuBar();
		break;
	}
}

void CutSceneManager::PhaseChange(ECutScenePhase _Phase)
{
	if (Phase != _Phase)
	{
		switch (_Phase)
		{
		case ECutScenePhase::Start:
			break;
		case ECutScenePhase::Enter:
			break;
		}
	}

	Phase = _Phase;
}
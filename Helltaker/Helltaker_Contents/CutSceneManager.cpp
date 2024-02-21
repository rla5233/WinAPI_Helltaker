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

bool CutSceneManager::IsLoad = false;

CutSceneManager::CutSceneManager()
{
}

CutSceneManager::~CutSceneManager()
{
}


void CutSceneManager::BeginPlay()
{
	ChapterManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Hell.png");
		ContentsHelper::LoadFolder("Scene\\Dialogue", "Death");
		ContentsHelper::LoadFolder("Scene\\Dialogue", "Success");

#ifdef DEBUG
		// ����� ��
		ContentsHelper::LoadFolder("UI", "Booper");
		ContentsHelper::LoadImg("BackGround", "DefaultBG.png");
		ContentsHelper::LoadImg("UI", "MenuBar_UnSelected.png");
		ContentsHelper::LoadImg("UI", "MenuBar_Selected.png");
#endif 
		IsLoad = true;
	}
}

void CutSceneManager::C_SpawnDialogue(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
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

	SceneCharacter = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	SceneCharacter->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	SceneCharacter->SetName(_Name);
	SceneCharacter->CreateImageRenderer(RenderOrder::Character);
	SceneCharacter->CreateNameRenderer(RenderOrder::Text);
	AllCutSceneActors.push_back(SceneCharacter);

	SceneCharacter->GetImageRenderer()->SetImage(_ImgName);
	SceneCharacter->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X * 0.255f, WinScale.Y * 0.611f} });

	SceneCharacter->GetNameRenderer()->SetText(_Text);
	SceneCharacter->GetNameRenderer()->SetFont("���� ����");
	SceneCharacter->GetNameRenderer()->SetTextSize(40);
	SceneCharacter->GetNameRenderer()->SetTransform({ { 0.0f, WinScale.Y * 0.317f }, { 0, 0 } });
	SceneCharacter->GetNameRenderer()->SetTextColor(HELLTAKER_RED);
}

void CutSceneManager::C_SpawnBooper()
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
	Booper->GetTextRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.0995f) }, { 0, 0 } });
	Booper->GetTextRenderer()->SetFont("���� ����");
	Booper->GetTextRenderer()->SetTextSize(35);
	Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	Booper->GetTextRenderer()->SetText(" ");
	AllCutSceneActors.push_back(Booper);
}

void CutSceneManager::C_BooperTextSet(std::string_view _Text)
{
	Booper->GetTextRenderer()->SetText(_Text);
}

void CutSceneManager::C_MenubarTextSet(int _Index, std::string_view _Text)
{
	MenuBar[_Index]->GetTextRenderer()->SetText(_Text);
}

void CutSceneManager::C_MenubarRenderActiveOff()
{
	for (UI* Menu : MenuBar)
	{
		Menu->AllRenderersActiveOff();
	}
}

void CutSceneManager::C_CharacterSetImage(std::string_view _Name)
{
	SceneCharacter->GetImageRenderer()->SetImage(_Name);
}

void CutSceneManager::C_CharacterSetTransform(FTransform _FTransform)
{
	SceneCharacter->GetImageRenderer()->SetTransform(_FTransform);
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
		MenuBar[i]->GetTextRenderer()->SetFont("���� ����");
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

void CutSceneManager::Enter(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_StateChange(ECutSceneState::Select);
	}
}

void CutSceneManager::Select(float _DeltaTime)
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
		SelectMenu();
	}
}

void CutSceneManager::BadEnd(float _DeltaTime)
{
	FailOrderCheck();
}

void CutSceneManager::BadEndSetting()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue->GetImageRenderer()->CreateAnimation("Scene_Death", "Death", 0, 8, 0.05f, false);
	Dialogue->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.816f, WinScale.Y * 0.444f } });
	Dialogue->GetImageRenderer()->ChangeAnimation("Scene_Death");
	SceneCharacter->AllRenderersActiveOff();
	Booper->GetTextRenderer()->SetTextColor(HELLTAKER_RED);
	Booper->GetImageRenderer()->ActiveOff();
	
	ChapterManager::M_StateChange(EChapterState::None);
	++FailOrder;
}

void CutSceneManager::FailOrderCheck()
{
	switch (FailOrder)
	{
	case 0:
		FailOrderInputCheck();
		break;
	case 1:
		BadEndSetting();
		break;
	case 2:
		ChapterRestart();
		break;
	}
}

void CutSceneManager::FailOrderInputCheck()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		++FailOrder;
	}
}

void CutSceneManager::ChapterRestart()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		ChapterManager::M_StateChange(EChapterState::Reset);
		C_StateChange(ECutSceneState::None);
	}	
}

void CutSceneManager::BadEndStart()
{
	Booper->GetImageRenderer()->ActiveOn();
	C_MenubarRenderActiveOff();

	FailOrder = 0;
}

void CutSceneManager::Success(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		SuccessEnd();
	}
}

void CutSceneManager::SuccessStart()
{
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	Booper->GetImageRenderer()->CreateAnimation("Scene_Success", "Success", 0, 7, 0.05f, false);
	Booper->GetImageRenderer()->ChangeAnimation("Scene_Success");
	Booper->GetImageRenderer()->SetTransform({ { 0.0f, WinScale.Y * 0.0275f }, { WinScale.X * 0.572f, WinScale.Y * 0.185f } });
	Booper->GetImageRenderer()->ActiveOn();
}


void CutSceneManager::SuccessEnd()
{
	for (AActor* Actor : AllCutSceneActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->AllRenderersActiveOff();
	}

	ChapterManager::M_StateChange(EChapterState::End);
	C_StateChange(ECutSceneState::None);
}

void CutSceneManager::SelectStart()
{
	Booper->GetImageRenderer()->ActiveOff();
	C_SpawnMenubar();
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

void CutSceneManager::CutSceneStart()
{
	ChapterManager::CutSceneStart();

	C_StateChange(ECutSceneState::Enter);
}

void CutSceneManager::Tick(float _DeltaTime)
{
	ChapterManager::Tick(_DeltaTime);

	C_StateUpdate(_DeltaTime);
}

void CutSceneManager::C_StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ECutSceneState::Enter:
		Enter(_DeltaTime);
		break;
	case ECutSceneState::Select:
		Select(_DeltaTime);
		break;
	case ECutSceneState::BadEnd:
		BadEnd(_DeltaTime);
		break;
	case ECutSceneState::Success:
		Success(_DeltaTime);
		break;
	}
}

void CutSceneManager::C_StateChange(ECutSceneState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ECutSceneState::Enter:
			EnterStart();
			break;
		case ECutSceneState::Select:
			SelectStart();
			break;
		case ECutSceneState::BadEnd:
			BadEndStart();
			break;
		case ECutSceneState::Success:
			SuccessStart();
			break;
		}
	}

	State = _State;
}

void CutSceneManager::LevelEnd(ULevel* _NextLevel)
{
	ChapterManager::LevelEnd(_NextLevel);

	for (AActor* Actor : AllCutSceneActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->Destroy(0.0f);
		Actor = nullptr;
	}

	MenuBar.clear();
	AllCutSceneActors.clear();
}
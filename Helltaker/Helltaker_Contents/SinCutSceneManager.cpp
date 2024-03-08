#include "SinCutSceneManager.h"

#include "Sin_Dialogue.h"
#include "BackGround.h"
#include "Character.h"
#include "Sin_Judge.h"
#include "UI.h"

const FVector SinCutSceneManager::FocusMenuScale = { 0.501f, 0.074f };
const FVector SinCutSceneManager::UnFocusMenuScale = { 0.475f, 0.065f };

SinCutSceneManager::SinCutSceneManager()
{
}

SinCutSceneManager::~SinCutSceneManager()
{
}

void SinCutSceneManager::BeginPlay()
{
	SinChapterManager::BeginPlay();
}

void SinCutSceneManager::C_CreateSceneBG()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector UpScale = { 1.0f, 0.154f };
	float UpPosY = WinScale.Y * UpScale.Y * 0.5f;
	BackGround* Up_BG = SpawnActor<BackGround>(SinUpdateOrder::BackGround);
	Up_BG->SetActorLocation({ WinScale.hX(), UpPosY });
	Up_BG->CreateImageRenderer(SinRenderOrder::BackGround);
	Up_BG->GetImageRenderer()->SetImage("DefaultBG.png");
	Up_BG->GetImageRenderer()->SetScale(WinScale * UpScale);
	AllCutSceneActors.push_back(Up_BG);

	FVector DownScale = { 1.0f, 0.34f };
	float DownPosY = WinScale.Y * (1.0f - DownScale.Y * 0.5f);
	BackGround* Down_BG = SpawnActor<BackGround>(SinUpdateOrder::BackGround);
	Down_BG->SetActorLocation({ WinScale.hX(), DownPosY });
	Down_BG->CreateImageRenderer(SinRenderOrder::BackGround);
	Down_BG->GetImageRenderer()->SetImage("DefaultBG.png");
	Down_BG->GetImageRenderer()->SetScale(WinScale * DownScale);
	AllCutSceneActors.push_back(Down_BG);
}

void SinCutSceneManager::CutSceneStart()
{
	SinChapterManager::CutSceneStart();

	C_CreateSceneBG();
	
	C_SpawnBooper();
	C_SpawnMenubar();

	// State º¯°æ Ãß°¡

}

void SinCutSceneManager::C_SpawnDialogue(int _PosType)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Sin_Dialogue>(SinUpdateOrder::UnderBackGround);
	Dialogue->SetActorLocation(WinScale.Half2D());
	Dialogue->SetName("Sin_Dialogue");
	Dialogue->SetSin(_PosType);

	AllCutSceneActors.push_back(Dialogue);
}

void SinCutSceneManager::C_SpawnJudge(std::string_view _ImgName, std::string_view _Text /* = " " */)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Judge = SpawnActor<Sin_Judge>(SinUpdateOrder::Mid);
	Judge->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	Judge->SetName("Sin_Judge");
	Judge->CreateImageRenderer(SinRenderOrder::Mid);
	Judge->CreateNameRenderer(SinRenderOrder::Top);

	Judge->GetImageRenderer()->SetImage(_ImgName);

	Judge->GetNameRenderer()->SetText(_Text);
	Judge->GetNameRenderer()->SetFont("¸¼Àº °íµñ");
	Judge->GetNameRenderer()->SetTextSize(40);
	Judge->GetNameRenderer()->SetTransform({ { 0.0f, WinScale.Y * 0.317f }, { 0, 0 } });
	Judge->GetNameRenderer()->SetTextColor(HELLTAKER_RED1);
	Judge->GetNameRenderer()->SetTextEffect(2);

	AllCutSceneActors.push_back(Judge);
}

void SinCutSceneManager::C_SpawnBooper()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.87f });
	Booper->SetName("Booper");
	Booper->CreateImageRenderer(SinRenderOrder::Top);
	Booper->GetImageRenderer()->SetImage(Booper->GetName());
	Booper->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X * 0.027f, WinScale.Y * 0.022f } });
	Booper->GetImageRenderer()->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->GetImageRenderer()->ChangeAnimation("Booper_Idle");
	Booper->CreateTextRenderer(SinRenderOrder::Top);
	Booper->GetTextRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.0995f) }, { 0, 0 } });
	Booper->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
	Booper->GetTextRenderer()->SetTextSize(35);
	Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	Booper->GetTextRenderer()->SetText(" ");

	AllCutSceneActors.push_back(Booper);
}

void SinCutSceneManager::C_BooperTextSet(std::string_view _Text)
{
	Booper->GetTextRenderer()->SetText(_Text);

	int LineCount = 1;
	for (size_t i = 0; i < _Text.size(); i++)
	{
		if ('\n' == _Text[i])
		{
			++LineCount;
		}
	}

	C_BooperSetTextPosition(LineCount);
}

void SinCutSceneManager::C_BooperSetTextPosition(int _LineCount)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	switch (_LineCount)
	{
	case 1:
		Booper->GetTextRenderer()->SetPosition({ 0.0f, WinScale.Y * (-0.12f) });
		break;
	case 2:
		Booper->GetTextRenderer()->SetPosition({ 0.0f, WinScale.Y * (-0.1f) });
		break;
	}
}

void SinCutSceneManager::C_SpawnMenubar(FVector _Pos, int _MenuBarCount)
{
	float interval = 0.0f;
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = WinScale * _Pos;

	MenuBarCount = _MenuBarCount;
	MenuBar.reserve(MenuBarCount);
	for (int i = 0; i < MenuBarCount; i++)
	{
		MenuBar.push_back(SpawnActor<UI>(static_cast<int>(UpdateOrder::UI)));
		MenuBar[i]->SetActorLocation({ Pos.X, Pos.Y + interval });
		MenuBar[i]->SetName("MenuBar");

		MenuBar[i]->CreateImageRenderer(RenderOrder::UI);

		MenuBar[i]->CreateTextRenderer(RenderOrder::Text);
		MenuBar[i]->GetTextRenderer()->SetTransform({ {0, -1}, {0, 0} });
		MenuBar[i]->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
		MenuBar[i]->GetTextRenderer()->SetTextSize(30);
		MenuBar[i]->GetTextRenderer()->SetText(" ");

		if (i == 0)
		{
			MenuBar[i]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
			MenuBar[i]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * FocusMenuScale });
			MenuBar[i]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
		}
		else
		{
			MenuBar[i]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
			MenuBar[i]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * UnFocusMenuScale });
			MenuBar[i]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		}

		interval += WinScale.Y * 0.074f;
		AllCutSceneActors.push_back(MenuBar[i]);
	}

	SetFocusMenuIndex(0);
}

void SinCutSceneManager::End(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		M_StateChange(ESinState::SinChage);
		C_StateChange(ESinSceneState::None);
	}
}

bool SinCutSceneManager::FocusMenuBarCheck()
{
	if (UEngineInput::IsDown('W') || UEngineInput::IsDown(VK_UP))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * UnFocusMenuScale });
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex - 1);
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * FocusMenuScale });
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
		return true;
	}
	else if (UEngineInput::IsDown('S') || UEngineInput::IsDown(VK_DOWN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_UnSelected.png");
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * UnFocusMenuScale });
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_GRAY);
		SetFocusMenuIndex(FocusMenuIndex + 1);
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetImage("MenuBar_Selected.png");
		MenuBar[FocusMenuIndex]->GetImageRenderer()->SetTransform({ {0, 0}, WinScale * FocusMenuScale });
		MenuBar[FocusMenuIndex]->GetTextRenderer()->SetTextColor(HELLTAKER_WHITE);
		return true;
	}
	else if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		SelectMenu();
	}

	return false;
}

void SinCutSceneManager::SetFocusMenuIndex(int _Index)
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

void SinCutSceneManager::Enter(float _DeltaTime)
{
	ResetCheck();
}

void SinCutSceneManager::ResetCheck()
{
	SinChapterManager::ResetCheck();

	if (UEngineInput::IsPress('R'))
	{
		C_StateChange(ESinSceneState::None);
	}
}

void SinCutSceneManager::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SinCutSceneManager::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSceneState::Enter:
		Enter(_DeltaTime);
		break;
	case ESinSceneState::End:
		End(_DeltaTime);
		break;
	}
}

void SinCutSceneManager::C_StateChange(ESinSceneState _State)
{
	if (State != _State)
	{	
		switch (_State)
		{
		case ESinSceneState::Enter:
			EnterStart();
			break;
		case ESinSceneState::End:
			EndStart();
			break;
		}
	}

	State = _State;
}

void SinCutSceneManager::LevelEnd(ULevel* _NextLevel)
{
	SinChapterManager::LevelEnd(_NextLevel);

	for (AActor* Actor : AllCutSceneActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->Destroy();
		Actor = nullptr;
	}
}
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

#include <EnginePlatform/EngineSound.h>

bool CutSceneManager::IsLoad = false;
const FVector CutSceneManager::FocusMenuScale = { 0.501f, 0.074f };
const FVector CutSceneManager::UnFocusMenuScale = { 0.475f, 0.065f };

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
		ContentsHelper::LoadImg("BackGround", "DefaultBG.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Hell.png");
		ContentsHelper::LoadImg("UI", "MenuBar_UnSelected.png");
		ContentsHelper::LoadImg("UI", "MenuBar_Selected.png");
		ContentsHelper::LoadImg("UI", "Small_LButton.png");
		ContentsHelper::LoadImg("UI", "Small_RButton.png");
		ContentsHelper::LoadFolder("UI", "Booper");
		ContentsHelper::LoadFolder("Scene\\Dialogue", "Death");
		ContentsHelper::LoadFolder("Scene\\Dialogue", "Success");

		ContentsHelper::LoadSound("Sound\\Effect", "booper_click.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "dialogue_start.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "dialogue_button_confirm.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "dialogue_button_focus.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "bad_end_screen.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "dialogue_success.wav");
		
		IsLoad = true;
	}
}

void CutSceneManager::C_CreateSceneBG()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* SceneBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::SceneBackGround));
	SceneBG->CreateSceneBackGround("DefaultBG");
	SceneBG->GetImageRenderer()->CameraEffectOff();
		
	AllCutSceneActors.push_back(SceneBG);
}

void CutSceneManager::C_SpawnDialogue(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	Dialogue->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.408f });
	Dialogue->SetName("Dialogue");
	Dialogue->CreateImageRenderer(RenderOrder::Scene);
	Dialogue->GetImageRenderer()->SetImage(_Name);
	Dialogue->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X, WinScale.Y * 0.5045f } });
	Dialogue->GetImageRenderer()->CameraEffectOff();
	AllCutSceneActors.push_back(Dialogue);
}

void CutSceneManager::C_SpawnCharacter(std::string_view _Name, std::string_view _ImgName, std::string_view _Text, const FVector& _Pos, const FVector& _Scale)
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	SceneCharacter = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	SceneCharacter->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	SceneCharacter->SetName(_Name);
	SceneCharacter->CreateImageRenderer(RenderOrder::Character);
	SceneCharacter->CreateNameRenderer(RenderOrder::Text);
	AllCutSceneActors.push_back(SceneCharacter);

	SceneCharacter->GetImageRenderer()->SetImage(_ImgName);
	SceneCharacter->GetImageRenderer()->SetTransform({ WinScale * _Pos, WinScale * _Scale });
	SceneCharacter->GetImageRenderer()->CameraEffectOff();

	SceneCharacter->GetNameRenderer()->SetText(_Text);
	SceneCharacter->GetNameRenderer()->SetFont("¸¼Àº °íµñ");
	SceneCharacter->GetNameRenderer()->SetTextSize(40);
	SceneCharacter->GetNameRenderer()->SetTransform({ { 0.0f, WinScale.Y * 0.317f }, { 0, 0 } });
	SceneCharacter->GetNameRenderer()->SetTextColor(HELLTAKER_RED1);
	SceneCharacter->GetNameRenderer()->SetTextEffect(2);
	SceneCharacter->GetNameRenderer()->CameraEffectOff();
}

void CutSceneManager::C_SpawnMenubar(FVector _Pos, int _MenuBarCount)
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
		MenuBar[i]->GetImageRenderer()->CameraEffectOff();

		MenuBar[i]->CreateTextRenderer(RenderOrder::Text);
		MenuBar[i]->GetTextRenderer()->SetTransform({ {0, -1}, {0, 0} });
		MenuBar[i]->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
		MenuBar[i]->GetTextRenderer()->SetTextSize(30);
		MenuBar[i]->GetTextRenderer()->SetText(" ");
		MenuBar[i]->GetTextRenderer()->CameraEffectOff();

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

void CutSceneManager::C_SpawnBooper()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Booper = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	Booper->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.87f });
	Booper->SetName("Booper");
	Booper->CreateImageRenderer(RenderOrder::UI);
	Booper->GetImageRenderer()->SetImage(Booper->GetName());
	Booper->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X * 0.027f, WinScale.Y * 0.022f } });
	Booper->GetImageRenderer()->CreateAnimation("Booper_Idle", "Booper", 0, 16, 0.05f, true);
	Booper->GetImageRenderer()->ChangeAnimation("Booper_Idle");
	Booper->GetImageRenderer()->CameraEffectOff();
	Booper->CreateTextRenderer(RenderOrder::Text);
	Booper->GetTextRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.0995f) }, { 0, 0 } });
	Booper->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
	Booper->GetTextRenderer()->SetTextSize(35);
	Booper->GetTextRenderer()->SetTextColor(Color8Bit(255, 255, 255, 0));
	Booper->GetTextRenderer()->SetText(" ");
	Booper->GetTextRenderer()->CameraEffectOff();
	AllCutSceneActors.push_back(Booper);
}

void CutSceneManager::C_BooperTextSet(std::string_view _Text)
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

void CutSceneManager::C_BooperChangeAnimation(std::string_view _AnimationName)
{
	Booper->GetImageRenderer()->ChangeAnimation(_AnimationName);
}

void CutSceneManager::C_BooperSetTransform(const FTransform& _Trans)
{
	Booper->GetImageRenderer()->SetTransform(_Trans);
}

void CutSceneManager::C_BooperSetTextPosition(int _LineCount)
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

void CutSceneManager::C_BooperImageRendererOn()
{
	Booper->GetImageRenderer()->ActiveOn();
}

void CutSceneManager::C_BooperImageRendererOff()
{
	Booper->GetImageRenderer()->ActiveOff();
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

void CutSceneManager::C_MenubarRenderActiveOn()
{
	for (UI* Menu : MenuBar)
	{
		Menu->AllRenderersActiveOn();
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

void CutSceneManager::C_CreateCharacterAnimation(
	std::string_view _AnimationName, 
	std::string_view _ImageName, 
	int _Start, int _End, 
	float _Inter, 
	bool _Loop /* = true*/)
{
	SceneCharacter->GetImageRenderer()->CreateAnimation(_AnimationName, _ImageName, _Start, _End, _Inter, _Loop);
}

void CutSceneManager::C_CreateCharacterAnimation(
	std::string_view _AnimationName,
	std::string_view _ImageName, 
	std::vector<int> _Indexs, 
	float _Inter, 
	bool _Loop /* = true */)
{
	SceneCharacter->GetImageRenderer()->CreateAnimation(_AnimationName, _ImageName, _Indexs, _Inter, _Loop);
}

void CutSceneManager::C_ChangeCharacterAnimation(std::string_view _AnimationName)
{
	SceneCharacter->GetImageRenderer()->ChangeAnimation(_AnimationName);
}

void CutSceneManager::C_ChangeDialogue(std::string_view _ImageName, const FTransform& _FTransform)
{
	Dialogue->GetImageRenderer()->SetImage(_ImageName);
	Dialogue->GetImageRenderer()->SetTransform(_FTransform);
	Dialogue->GetImageRenderer()->ActiveOn();
}

void CutSceneManager::Enter(float _DeltaTime)
{
	ResetCheck();
	
	if ( (false == SceneCharacter->IsImgMoveOn())
	&& (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN)))
	{
		C_StateChange(ECutSceneState::Select);
		UEngineSound::SoundPlay("booper_click.wav");
	}
}

void CutSceneManager::Select()
{
	ResetCheck();
	
	if (true == FocusMenuBarCheck())
	{
		UEngineSound::SoundPlay("dialogue_button_focus.wav");
	}
}

void CutSceneManager::SelectStart()
{
	Booper->GetImageRenderer()->ActiveOff();
	C_SpawnMenubar();
}

void CutSceneManager::BadEnd()
{
	FailOrderCheck();
}

void CutSceneManager::BadEndStart()
{
	Booper->GetImageRenderer()->ActiveOn();
	C_MenubarRenderActiveOff();

	FailOrder = 0;
	UEngineSound::SoundPlay("dialogue_button_confirm.wav");
}

void CutSceneManager::BadEndSetting()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue->GetImageRenderer()->CreateAnimation("Scene_Death", "Death", 0, 8, 0.05f, false);
	Dialogue->GetImageRenderer()->SetTransform({ { 0, 0 }, { WinScale.X * 0.816f, WinScale.Y * 0.444f } });
	Dialogue->GetImageRenderer()->ChangeAnimation("Scene_Death");
	SceneCharacter->AllRenderersActiveOff();
	Booper->GetTextRenderer()->SetTextColor(HELLTAKER_RED2);
	Booper->GetTextRenderer()->SetTextEffect(2);
	Booper->GetImageRenderer()->ActiveOff();
	
	ChapterManager::M_StateChange(EChapterState::None);
	UEngineSound::SoundPlay("bad_end_screen.wav");
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

void CutSceneManager::ResetCheck()
{
	ChapterManager::ResetCheck();

	if (UEngineInput::IsPress('R'))
	{
		C_StateChange(ECutSceneState::None);
	}
}

void CutSceneManager::Success(float _DeltaTime)
{
	ResetCheck();

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

	UEngineSound::SoundPlay("dialogue_success.wav");
}


void CutSceneManager::SuccessEnd()
{
	UEngineSound::SoundPlay("booper_click.wav");

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

void CutSceneManager::CutSceneStart()
{
	ChapterManager::CutSceneStart();

	C_CreateSceneBG();

	C_StateChange(ECutSceneState::None);
	C_StateChange(ECutSceneState::Enter);
	
	UEngineSound::SoundPlay("dialogue_start.wav");
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
		Select();
		break;
	case ECutSceneState::BadEnd:
		BadEnd();
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

bool CutSceneManager::FocusMenuBarCheck()
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
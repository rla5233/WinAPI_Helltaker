#include "SinCutSceneManager.h"

#include "Sin_Dialogue.h"
#include "BackGround.h"
#include "UI.h"

bool SinCutSceneManager::IsLoad = false;

SinCutSceneManager::SinCutSceneManager()
{
}

SinCutSceneManager::~SinCutSceneManager()
{
}

void SinCutSceneManager::BeginPlay()
{
	SinChapterManager::BeginPlay();

	if (false == IsLoad)
	{


		// ¼öÁ¤ (Á¦°Å)
		ContentsHelper::LoadImg("BackGround", "DefaultBG.png");
		ContentsHelper::LoadFolder("UI", "Booper");

		IsLoad = true;
	}
}

void SinCutSceneManager::C_CreateSceneBG()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector UpScale = { 1.0f, 0.15f };
	float UpPosY = WinScale.Y * UpScale.Y * 0.5f;
	BackGround* Up_BG = SpawnActor<BackGround>(SinUpdateOrder::BackGround);
	Up_BG->SetActorLocation({ WinScale.hX(), UpPosY });
	Up_BG->CreateImageRenderer(SinRenderOrder::BackGround);
	Up_BG->GetImageRenderer()->SetImage("DefaultBG.png");
	Up_BG->GetImageRenderer()->SetScale(WinScale * UpScale);
	AllCutSceneActors.push_back(Up_BG);

	FVector DownScale = { 1.0f, 0.4f };
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
	C_CreateSceneBG();

	C_CreateDialogue();
	C_SpawnBooper();
	// ÄÆ½Å »óÅÂ º¯°æ

}

void SinCutSceneManager::C_CreateDialogue()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Sin_Dialogue>(SinUpdateOrder::UnderBackGround);
	Dialogue->SetActorLocation(WinScale.Half2D());
	Dialogue->SetName("Sin_Dialogue");

	AllCutSceneActors.push_back(Dialogue);
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

void SinCutSceneManager::EnterStart()
{
}

void SinCutSceneManager::Enter(float _DeltaTime)
{
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
	default:
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
		default:
			break;
		}
	}

	State = _State;
}
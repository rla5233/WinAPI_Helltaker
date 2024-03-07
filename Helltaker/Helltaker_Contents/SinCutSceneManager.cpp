#include "SinCutSceneManager.h"

#include "Sin_Dialogue.h"
#include "BackGround.h"

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


		// 수정 (제거)
		ContentsHelper::LoadImg("BackGround", "DefaultBG.png");

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
	//C_CreateSceneBG();
	
	C_CreateDialogue();

	// 컷신 상태 변경

}

void SinCutSceneManager::C_CreateDialogue()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Dialogue = SpawnActor<Sin_Dialogue>(SinUpdateOrder::UnderBackGround);
	Dialogue->SetActorLocation(WinScale.Half2D());
	Dialogue->SetName("Sin_Dialogue");

	AllCutSceneActors.push_back(Dialogue);
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
#include "SinCutSceneManager.h"

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


		IsLoad = true;
	}
}

void SinCutSceneManager::C_CreateSceneBG()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector UpScale = { 1.0f, 0.2f };
	float UpPosY = WinScale.Y * 0.3f;
	BackGround* Up_BG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	Up_BG->SetActorLocation({ WinScale.hX(), UpPosY });
	Up_BG->CreateImageRenderer(SinRenderOrder::BackGround);
	Up_BG->GetImageRenderer()->SetImage("DefaultBG.png");
	Up_BG->GetImageRenderer()->SetScale(WinScale * UpScale);

	AllCutSceneActors.push_back(Up_BG);
}

void SinCutSceneManager::CutSceneStart()
{
	// 검은색 배경 생성

	


	// 컷신 상태 변경

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
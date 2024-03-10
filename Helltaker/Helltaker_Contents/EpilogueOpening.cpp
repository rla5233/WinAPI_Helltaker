#include "EpilogueOpening.h"

#include "Epilogue.h"
#include "Scene.h"

#include <EnginePlatform/EngineSound.h>


bool EpilogueOpening::IsLoad = false;

const std::vector<const char*> EpilogueOpening::Epil_Opening_Script =
{
	/* 0  Script 1 */ "그리하여 당신의 여정은 끝이 났다.",
	/* 1  Script 2 */ "악마들을 지옥에서 무사히 데려왔다.\n그리고 헬테이커라고 알려지게 됐지.",
	/* 2  Script 3 */ "하지만 쉽지 않은 삶일 터이다.\n분명 짧고, 또 고난으로 가득하리.",
	/* 3  Script 4 */ "하지만 어떻게 살아가든 삶이란 고달픈 법.\n그러니 그 순간만큼은 즐기는 게 낫겠지.",
};

EpilogueOpening::EpilogueOpening()
{
}

EpilogueOpening::~EpilogueOpening()
{
}


void EpilogueOpening::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_001.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_002.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_003.png");

		AddChapterSet("EpilogueOpening");

		IsLoad = true;
	}
}

void EpilogueOpening::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	StateChange(EEpilogueState::Enter);
}

void EpilogueOpening::EnterStart()
{
	C_SpawnBooper();

	C_BooperTextSet(Epil_Opening_Script[0]);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");

	OrderCount = 0;
}

void EpilogueOpening::Enter()
{
	switch (OrderCount)
	{
	case 0:
		Enter1();
		break;
	default:
		EnterCutScene();
		break;
	}
}

void EpilogueOpening::Enter1()
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
		++OrderCount;
	}
}

void EpilogueOpening::EnterCutScene()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		if (4 == OrderCount)
		{
			StateChange(EEpilogueState::Change);
			return;
		}

		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.67f, 0.6f };
		FVector Pos = { 0.0f, -0.02f };

		std::string ImgName = "CutScene_Epil_00";
		ImgName += std::to_string(OrderCount) + ".png";
		if (1 == OrderCount)
		{
			C_SpawnDialogue("CutScene_Epil_001.png");
			C_GetDialogue()->GetImageRenderer()->SetTransform({ Pos * WinScale, Scale * WinScale });
		}
		else
		{
			C_ChangeDialogue(ImgName, { Pos * WinScale, Scale * WinScale });
		}

		C_BooperTextSet(Epil_Opening_Script[OrderCount]);
		UEngineSound::SoundPlay("booper_click.wav");

		++OrderCount;
	}
}

void EpilogueOpening::ChangeStart()
{
	TransitionOn();
}

void EpilogueOpening::Change()
{
	if (19 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
	{
		ChangeChapter();
	}
}

void EpilogueOpening::Tick(float _DeltaTime)
{
	HellTakerManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void EpilogueOpening::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EEpilogueState::Enter:
		Enter();
		break;
	case EEpilogueState::Change:
		Change();
		break;
	}
}

void EpilogueOpening::StateChange(EEpilogueState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EEpilogueState::Enter:
			EnterStart();
			break;
		case EEpilogueState::Change:
			ChangeStart();
			break;
		}
	}

	State = _State;
}

void EpilogueOpening::ChangeChapter()
{
	HellTakerManager::ChangeChapter();

	CreateChapter<Epilogue>("Epilogue");
	GEngine->ChangeLevel("Epilogue");
}
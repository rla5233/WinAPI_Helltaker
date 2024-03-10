#include "Epilogue.h"

#include "Scene.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const std::vector<const char*> Epilogue::Epilogue_Script =
{
	/* 0  Script 1 */ "그리하여 당신의 여정은 끝이 났다.",
	/* 1  Script 2 */ "악마들을 지옥에서 무사히 데려왔다.\n그리고 헬테이커라고 알려지게 됐지.",
	/* 2  Script 3 */ "하지만 쉽지 않은 삶일 터이다.\n분명 짧고, 또 고난으로 가득하리.",
	/* 3  Script 4 */ "하지만 어떻게 살아가든 삶이란 고달픈 법.\n그러니 그 순간만큼은 즐기는 게 낫겠지.",
	


};

Epilogue::Epilogue()
{
}

Epilogue::~Epilogue()
{
}

void Epilogue::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_001.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_002.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Epil_003.png");

		AddChapterSet("Epilogue");

		IsLoad = true;
	}
}

void Epilogue::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	StateChange(EEpilogueState::Enter);
}

void Epilogue::Tick(float _DeltaTime)
{
	HellTakerManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Epilogue::EnterStart()
{
	C_SpawnBooper();

	C_BooperTextSet(Epilogue_Script[0]);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");

	OrderCount = 0;
}

void Epilogue::Enter()
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

void Epilogue::Enter1()
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
		++OrderCount;
	}
}

void Epilogue::EnterCutScene()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		if (4 == OrderCount)
		{
			StateChange(EEpilogueState::Idle);
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

		C_BooperTextSet(Epilogue_Script[OrderCount]);
		UEngineSound::SoundPlay("booper_click.wav");
		
		++OrderCount;
	}
}

void Epilogue::IdleStart()
{
	AllCutSceneActorOff();
	TransitionOn();

	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, true , true , false },
		{ false, true , true , true , true , true , false },
		{ false, true , true , true , true , false, false },
		{ true , true , false, false, false, false, false },
		{ true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.32f, 0.208f });

	CreateBG("ChapterBG_001");
	M_SpawnHero({ 5, 0 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.049f, WinScale.Y * 0.08f };
	FVector Pos = { WinScale.X * (-0.003f), WinScale.Y * (-0.01f) };
	M_SpawnDemon({ 6, 5 }, "PandeMonica", { Pos, Scale });
}

void Epilogue::Idle()
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
	}


}

void Epilogue::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EEpilogueState::Enter:
		Enter();
		break;
	case EEpilogueState::Idle:
		Idle();
		break;
	}
}

void Epilogue::StateChange(EEpilogueState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EEpilogueState::Enter:
			EnterStart();
			break;
		case EEpilogueState::Idle:
			IdleStart();
			break;
		}
	}

	State = _State;
}


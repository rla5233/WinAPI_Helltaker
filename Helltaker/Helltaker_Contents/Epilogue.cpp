#include "Epilogue.h"

#include "Scene.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const std::vector<const char*> Epilogue::Epilogue_Script =
{
	/* 0  Script 1 */ "그리하여 당신의 여정은 끝이 났다.",
	/* 1  Script 2 */ "악마들을 지옥에서 무사히 데려왔다.\n그리고 헬테이커라고 알려지게 됐지.",
	


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

void Epilogue::Enter(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		Enter1();
		break;
	case 1:
		Enter2();
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

void Epilogue::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.67f, 0.6f };
		FVector Pos = { 0.0f, -0.02f };

		C_SpawnDialogue("CutScene_Epil_001.png");
		C_GetDialogue()->GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });

		C_BooperTextSet(Epilogue_Script[1]);

		++OrderCount;
	}
}

void Epilogue::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EEpilogueState::Enter:
		Enter(_DeltaTime);
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
		}
	}

	State = _State;
}


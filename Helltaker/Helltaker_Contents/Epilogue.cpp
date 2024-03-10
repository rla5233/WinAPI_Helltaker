#include "Epilogue.h"

#include "Scene.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const std::vector<const char*> Epilogue::Epilogue_Script =
{
	/* 0  Script 1 */ "�׸��Ͽ� ����� ������ ���� ����.",
	/* 1  Script 2 */ "�Ǹ����� �������� ������ �����Դ�.\n�׸��� ������Ŀ��� �˷����� ����.",
	/* 2  Script 3 */ "������ ���� ���� ���� ���̴�.\n�и� ª��, �� ������ �����ϸ�.",
	/* 3  Script 4 */ "������ ��� ��ư��� ���̶� ����� ��.\n�׷��� �� ������ŭ�� ���� �� ������.",
	


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
	case 4:
		StateChange(EEpilogueState::Idle);
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

}

void Epilogue::Idle()
{

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


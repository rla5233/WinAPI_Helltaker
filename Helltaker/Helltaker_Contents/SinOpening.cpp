#include "SinOpening.h"

#include "Sin_Dialogue.h"
#include "Sin_Judge.h"
#include "Character.h"
#include "Scene.h"
#include "UI.h"

#include "SinChapter1.h"

#include <EnginePlatform/EngineSound.h>

bool SinOpening::IsLoad = false;
const std::vector<const char*> SinOpening::SinOpening_Script =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 2  Script 1  */ "��ġ õ ���� ���� �� ���� �����̴�. ������ �ұ���\n��׶���... ����Ƶ� ����� ���� ����ִ� �� ����.",
	/* 3  Script 2  */ "Ĩ���� �༮, ������ ã�Ҵ�!\n�� ���� ���� �� ����.",
	/* 4  Script 3  */ "���� �Բ� ���� �ð��� ������ �� �Ŵ�.",
	/* 5  Script 4  */ "�˾��� ��迡 �õ��� �ɾ��! �÷��� ���� ���� ����!"
};

SinOpening::SinOpening()
{
}

SinOpening::~SinOpening()
{
}

void SinOpening::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Scene\\Characters\\Jud_Arm", "L_Arm");
		ContentsHelper::LoadFolder("Scene\\Characters\\Jud_Arm", "R_Arm");

		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Intro");

		AddChapterSet("SinOpening");
		IsLoad = true;
	}
}

void SinOpening::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");

	M_StateChange(ESinState::CutScene);
}

void SinOpening::CutSceneStart()
{
	SinChapterManager::CutSceneStart();
	GetTransitionActor()->AllRenderersActiveOn();
	GetTransitionActor()->ActiveOn();
	
	C_SpawnBooper();
	C_BooperTextSet(SinOpening_Script[2]);

	C_SpawnJudge("Jud_Intro");

	C_StateChange(ESinSceneState::Enter);
}

void SinOpening::CutScene(float _DeltaTime)
{}

void SinOpening::EnterStart()
{
	OrderCount = 0;
}

void SinOpening::Enter(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0 :
		TransitionCheck();
		break;
	case 1:
		Enter1();
		break;
	case 2:
		Enter2();
		break;
	case 3:
		Enter3();
		break;
	}
}

void SinOpening::TransitionCheck()
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
		++OrderCount;
	}
}

void SinOpening::Enter1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_CreateSceneBG();
		C_SpawnDialogue(0);
		
		C_GetJudge()->GetNameRenderer()->SetText(SinOpening_Script[0]);
		// ���� (ĳ���� �߰�)

		C_BooperTextSet(SinOpening_Script[3]);
		++OrderCount;
	}
}

void SinOpening::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(SinOpening_Script[4]);
		++OrderCount;
	}
}

void SinOpening::Enter3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetDialogue()->StateChange(ESinDialogueState::Lightning);
		C_GetBooper()->AllRenderersActiveOff();
		C_GetJudge()->GetNameRenderer()->ActiveOff();
		++OrderCount;
	}
}

void SinOpening::EndStart()
{
	SinCutSceneManager::EndStart();

	C_GetJudge()->GetNameRenderer()->SetText(SinOpening_Script[1]);
	C_GetJudge()->GetNameRenderer()->ActiveOn();
	
	C_BooperTextSet(SinOpening_Script[5]);
	C_GetBooper()->AllRenderersActiveOn();
}

void SinOpening::ChangeChapter()
{
	SinChapterManager::ChangeChapter();

	CreateChapter<SinChapter1>("SinChapter1");
	GEngine->ChangeLevel("SinChapter1");
}

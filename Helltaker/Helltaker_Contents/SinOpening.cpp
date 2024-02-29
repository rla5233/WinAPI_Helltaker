#include "SinOpening.h"

#include "Scene.h"

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
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_LitHell.png");

		IsLoad = true;
	}
}

void SinOpening::LevelStart(ULevel * _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);

	M_StateChange(EChapterState::CutScene);
}

void SinOpening::CutSceneStart()
{
	CutSceneManager::CutSceneStart();
	
	C_SpawnBooper();

	C_BooperTextSet(SinOpening_Script[2]);
	C_BooperSetTextPosition(2);
	EnterOrder = 0;
}

void SinOpening::Enter(float _DeltaTime)
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
	}

	switch (EnterOrder)
	{
	case 0:
		EnterOrder1();
		break;
	case 1:
		break;
	}

}

void SinOpening::EnterOrder1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_SpawnDialogue("DialBG_LitHell.png");
		C_SpawnDialogue("DialogueBG_Sin_001.png");
		++EnterOrder;
	}
}

void SinOpening::EnterStart()
{

	//C_SpawnCharacter("Cer", "Cer_Idle.png", Chap3_Script[0]);
}

void SinOpening::ChangeChapter()
{}


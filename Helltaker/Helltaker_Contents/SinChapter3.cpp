#include "SinChapter3.h"

#include "Sin_Judge.h"
#include "UI.h"

#include "SinChapter4.h"

bool SinChapter3::IsLoad = false;
const std::vector<const char*> SinChapter3::SinChap3_Script =
{
	/* 0  Demon	   */ "���� ��Ұ� ������Ʈ",
	/* 1 Script 1  */ "���� �罽�� �μ��� �������� �� ���� �� ������?",
	/* 2 Script 2  */ "����� �Ǹ���, �׸��� �Ǹ��� ������ ���´�.",
	/* 3 Script 3  */ "�׸��� ������ �罽�� ���� ��ſ� ������.",
	/* 4 Script 4  */ "�׷�! �װ� ���� ��� �͵��� ��ȸ�϶�!",

	/* 5 MenuBar 1  */ "�� ��� ��Ÿ���� ������ ��µ�.",
  	/* 6 MenuBar 2  */ "�� �� �����ִµ�! 10�� ������ 10��!",
	/* 7 Script 1   */ "������! �⸸���� �� ����� ��� ���� ����!",

	/* 8 MenuBar 1  */ "�˾�. �׷��� ���� ������ ����.",
	/* 9 MenuBar 2  */ "�� ���鵵 ������ ���!",
	/* 10 Script 1  */ "�׷�? �׷��ٸ�, '����!'��� �ؾ߰���?",
	/* 11 Script 2  */ "���� �ٽ� �÷��� �����Ѵ�!",

	/* 12  Demon	*/ "�󽺷��� �Ǹ� �����",
	/* 13 Script 1  */ "����ī�� ����� ����. �ⲯ ã�� �׽��۰� ģ���� �װ�\n�����.",

	/* 14  Demon	*/ "��ū���� �Ǹ� ������",
	/* 15 Script 1  */ "�� ����� �̷��� ���� ��ũ���������� �ϰ� �ƾ�.",

	/* 16 Demon	    */ "������ �Ǹ� �𵥿콺",
	/* 17 Script 1  */ "���� �� ȥ�� �������� ��...",
};

SinChapter3::SinChapter3()
{
}

SinChapter3::~SinChapter3()
{
}

void SinChapter3::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_BindAnim_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_BindAnim_002.png");
		ContentsHelper::LoadImg("Scene\\Characters\\Jud_Pose", "Jud_PoseAnim_001.png");
		ContentsHelper::LoadImg("Scene\\Characters\\", "PentaGraphic.png");

		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_BindAnim");
		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Pose");
		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Fly");

		AddChapterSet("SinChapter3");

		IsLoad = true;
	}
}

void SinChapter3::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(3);

	M_StateChange(ESinState::Intro);
}

void SinChapter3::Phase1_Start()
{
	SinChapterManager::Phase1_Start();
	SetPhase1_StartDelayTime(2.0f);

	M_SetSmallChainVecSize(28, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(3, 0);
	
	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);

	M_CreateSmallVerChain_P1(1, 2);
	M_CreateSmallVerChain_P1(5, 2);

	M_CreateSmallVerChain_P1(0, 3);
	M_CreateSmallVerChain_P1(6, 3);

	M_CreateSmallHorChain_P1(4, 5);
	
	M_CreateSmallHorChain_P1(2, 6);

	M_CreateSmallVerChain_P1(0, 7);
	M_CreateSmallVerChain_P1(6, 7);

	M_CreateSmallHorChain_P1(0, 8);

	M_CreateSmallVerChain_P1(1, 9);
	M_CreateSmallVerChain_P1(5, 9);

	M_CreateSmallHorChain_P1(4, 10);

	M_CreateSmallVerChain_P1(2, 11);
	M_CreateSmallVerChain_P1(4, 11);

	M_CreateSmallHorChain_P1(1, 12);

	M_CreateSmallVerChain_P1(3, 13);
	
	M_CreateSmallVerChain_P1(0, 15);
	M_CreateSmallVerChain_P1(3, 15);
	M_CreateSmallVerChain_P1(6, 15);

	M_CreateSmallVerChain_P1(1, 16);
	M_CreateSmallVerChain_P1(2, 16);
	M_CreateSmallVerChain_P1(4, 16);
	M_CreateSmallVerChain_P1(5, 16);
	
	M_CreateSmallHorChain_P1(2, 17);

	M_CreateSmallVerChain_P1(0, 18);
	M_CreateSmallVerChain_P1(6, 18);

	M_CreateSmallVerChain_P1(3, 19);
	M_CreateSmallHorChain_P1(0, 19);
	M_CreateSmallHorChain_P1(4, 19);

	M_CreateSmallVerChain_P1(2, 20);
	M_CreateSmallVerChain_P1(4, 20);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(6, 21);
	M_CreateSmallHorChain_P1(1, 21);

	M_CreateSmallVerChain_P1(1, 22);
	M_CreateSmallVerChain_P1(5, 22);

	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallHorChain_P1(4, 23);

	M_CreateSmallVerChain_P1(2, 24);
	M_CreateSmallVerChain_P1(3, 24);
	M_CreateSmallVerChain_P1(4, 24);

	M_CreateSmallVerChain_P1(1, 25);
	M_CreateSmallVerChain_P1(2, 25);
	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallVerChain_P1(4, 25);
	M_CreateSmallVerChain_P1(5, 25);

	M_CreateSmallVerChain_P1(0, 26);
	M_CreateSmallVerChain_P1(6, 26);

	M_CreateSmallVerChain_P1(0, 27);
	M_CreateSmallVerChain_P1(1, 27);
	M_CreateSmallVerChain_P1(5, 27);
	M_CreateSmallVerChain_P1(6, 27);
}

void SinChapter3::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 0);
	M_CreateHitChain(ESinHitChainType::Right, 2);
	M_CreateHitChainHp("3. ������ �罽");

	M_SetSmallChainVecSize(4, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(1, 0);
	M_CreateSmallHorChain_P2(0, 0);

	M_CreateSmallHorChain_P2(0, 1);
	M_CreateSmallHorChain_P2(4, 1);

	M_CreateSmallVerChain_P2(5, 2);
	M_CreateSmallVerChain_P2(6, 2);
	M_CreateSmallHorChain_P2(4, 2);

	M_CreateSmallVerChain_P2(0, 3);
	M_CreateSmallVerChain_P2(6, 3);
}

void SinChapter3::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();

	C_SpawnDialogue(1);

	FVector Scale = { 0.658f, 0.693f };
	FVector Pos = { 0.0f, -0.042f };
	C_SpawnJudge("Jud_BindAnim_001.png", SinChap3_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap3_Script[1]);
}

void SinChapter3::EnterStart()
{
	OrderCount = 0;
}

void SinChapter3::Enter(float _DeltaTime)
{
	SinCutSceneManager::Enter(_DeltaTime);

	switch (OrderCount)
	{
	case 0:
		Enter1();
		break;
	case 1:
		Enter2();
		break;
	case 2:
		Enter3();
		break;
	case 3:
		Enter4();
		break;
	case 4:
		Enter5();
		break;
	case 5:
		Enter6();
		break;
	case 6:
		Enter7();
		break;
	}
}

void SinChapter3::Enter1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		// ���� (jud �ִϸ��̼� �߰�)
		C_BooperTextSet(SinChap3_Script[2], true);
		++OrderCount;
	}
}

void SinChapter3::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.247f, 0.561f };
		FVector Pos = { 0.015f, 0.02f };
		// ���� (jud �ִϸ��̼� �߰�)

		C_BooperTextSet(SinChap3_Script[3], true);
		++OrderCount;
	}
}

void SinChapter3::Enter3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetJudge()->AllRenderersActiveOff();

		FVector Scale = { 0.256f, 0.567f };
		FVector Pos = { 0.014f, 0.021f };
		C_SpawnCharacter("Zd", "Zd_Idle.png", SinChap3_Script[12], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[13], true);
		++OrderCount;
	}
}

void SinChapter3::Enter4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.21f, 0.576f };
		FVector Pos = { 0.0f, 0.017f };
		C_CharacterChange("Mal", "Mal_Puzzled.png", SinChap3_Script[14], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[15], true);
		++OrderCount;
	}
}

void SinChapter3::Enter5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.194f,  0.605f };
		FVector Pos = { 0.0f, 0.0f };
		C_CharacterChange("Mod", "Mod_Idle.png", SinChap3_Script[16], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[17], true);
		++OrderCount;
	}
}

void SinChapter3::Enter6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetSceneCharacter()->AllRenderersActiveOff();

		FVector Scale = { 0.558f, 0.693f };
		FVector Pos = { 0.0f, -0.0402f };
		C_JudgeChange("Jud_Intro_004.png", Pos, Scale);
		C_GetJudge()->AllRenderersActiveOn();
		C_GetJudge()->Character::StateChange(ECharacterState::None);
		C_GetJudge()->Character::StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[4], true);
		++OrderCount;
	}
}

void SinChapter3::Enter7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		UEngineSound::SoundPlay("booper_click.wav");
		C_StateChange(ESinSceneState::Select);
	}
}

void SinChapter3::SelectStart()
{
	SinCutSceneManager::SelectStart();

	C_MenubarTextSet(0, SinChap3_Script[5]);
	C_MenubarTextSet(1, SinChap3_Script[6]);
	OrderCount = 0;
}

void SinChapter3::SelectMenu()
{
	switch (OrderCount)
	{
	case 0:
		Select1();
		break;
	case 1:
		Select2();
		break;
	case 2:
		Select3();
		break;
	case 3:
		Select4();
		break;
	}
}


void SinChapter3::Select1()
{
	UEngineSound::SoundPlay("dialogue_button_confirm.wav");
	C_MenubarRenderActiveOff();
	C_BooperTextSet(SinChap3_Script[7]);
	C_GetBooper()->AllRenderersActiveOn();
	++OrderCount;
}

void SinChapter3::Select2()
{
	UEngineSound::SoundPlay("booper_click.wav");
	C_GetBooper()->GetImageRenderer()->ActiveOff();
	C_MenubarTextSet(0, SinChap3_Script[8]);
	C_MenubarTextSet(1, SinChap3_Script[9]);
	C_MenubarRenderActiveOn();
	++OrderCount;
}

void SinChapter3::Select3()
{
	UEngineSound::SoundPlay("dialogue_button_confirm.wav");
	C_GetBooper()->GetImageRenderer()->ActiveOn();

	FVector Scale = { 0.39f, 0.693f };
	FVector Pos = { 0.0f, -0.04f };
	C_JudgeChange("Jud_PoseAnim_001.png", Pos, Scale);
	C_BooperTextSet(SinChap3_Script[10]);
	C_MenubarRenderActiveOff();
	++OrderCount;
}

void SinChapter3::Select4()
{
	C_BooperTextSet(SinChap3_Script[11], true);
	C_GetJudge()->StateChange(ESinJudgeState::Chap3_Fly);
	C_StateChange(ESinSceneState::End);
}

void SinChapter3::ChangeChapter()
{
	SinManager::ChangeChapter();

	CreateChapter<SinChapter4>("SinChapter4");
	GEngine->ChangeLevel("SinChapter4");
}

#include "SinChapter4.h"

#include "Sin_Judge.h"
#include "UI.h"

#include "EpilogueOpening.h"

bool SinChapter4::IsLoad = false;
const std::vector<const char*> SinChapter4::SinChap4_Script =
{
	/* 0  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 1  Script 1  */ "������ ������ ���۵Ǳ� ���� ���� ���̶� �ִ���?",
	/* 2  MenuBar1  */ "�� ���� ã�� ���� �� ��ȸ������.",
	/* 3  MenuBar2  */ "�ʿ��� ������ ���� �� ������ �˾ǵ� ������ ����.",

	/* 4  Script 2  */ "���� �ƺδ� ����ġ��! ���� ��ư� ������ ��!",
	/* 5  MenuBar1  */ "�׸��� ���� �̷��� �� �����ݾ�.",
	/* 6  MenuBar2  */ "�� ���� ��Ÿ���� ���ٰ� ���߾���?",

	/* 7  Script 3  */ "���ݾ�, ���� ���� �̷��� ���� ������. ������ �̹� �����\nȮ���ƾ�. �� ���ָ� ���� �� ���ٰ�.",
	/* 8  Script 4  */ "�׷���... �װ� �ٽ� ������ ������ �ٴ����� �ʴ´ٸ� �ڷ�\n�̷� ���� �ְ���",
	/* 9  Script 5  */ "����� �̹� ��������. �� �ʸ� ���̰�, �� �÷��� �޾ƾ� ����.\n������ �װ� �� ������ �ʿ�� ����...",
	/* 10 Script 6  */ "�׷��� �� ���� �� �˰� �� �� �տ��� �������!",
	/* 11 Script 7  */ "...",
	/* 12 Script 8  */ "... ...",
	/* 13 Script 9  */ "... ... ...",
	/* 14 Script 10 */ "���� �ȴٰ� ���ݾ�! �� �����!	",
	/* 15 Script 11 */ "��? �� �Ϸ��� �������? ������ ����!",

	/* 16 Script 12 */ "������ �� ���̷��� ������ ȭ�Ű� �� ���� �Ʒ���\n��ڴٰ�?",
	/* 17 MenuBar1  */ "�ٸ��� �ٶ����� �ʾ�.",
	/* 18 MenuBar2  */ "�� �Ϸ��� �̹� �� ���� �͵� �־�, ������.",

	/* 19 Script 13 */ "��, �����̾�?",
	/* 20 Script 14 */ "�̹� ����� �� �Ƿʶ� �Ÿ��� �� ���翡, �� �� ������ �� ��\n�͵� ���ھ�.",
};

SinChapter4::SinChapter4()
{
}

SinChapter4::~SinChapter4()
{
}

void SinChapter4::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Resign.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Shock.png");

		AddChapterSet("SinChapter4");

		IsLoad = true;
	}
}

void SinChapter4::LevelStart(ULevel* _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(4);

	M_StateChange(ESinState::Intro);
}

void SinChapter4::Phase1_Start()
{
	SinChapterManager::Phase1_Start();
	SetPhase1_StartDelayTime(1.0f);

	M_SetSmallChainVecSize(30, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(3, 0);
	M_CreateSmallHorChain_P1(2, 0);

	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);
	M_CreateSmallHorChain_P1(1, 1);
	M_CreateSmallHorChain_P1(3, 1);

	M_CreateSmallVerChain_P1(0, 2);
	M_CreateSmallVerChain_P1(6, 2);
	M_CreateSmallHorChain_P1(0, 2);
	M_CreateSmallHorChain_P1(4, 2);

	M_CreateSmallVerChain_P1(0, 3);
	M_CreateSmallVerChain_P1(3, 3);
	M_CreateSmallHorChain_P1(1, 3);

	M_CreateSmallVerChain_P1(1, 4);
	M_CreateSmallVerChain_P1(4, 4);
	M_CreateSmallHorChain_P1(3, 4);

	M_CreateSmallVerChain_P1(2, 5);
	M_CreateSmallVerChain_P1(5, 5);
	M_CreateSmallHorChain_P1(2, 5);

	M_CreateSmallVerChain_P1(3, 6);
	M_CreateSmallVerChain_P1(6, 6);
	M_CreateSmallHorChain_P1(3, 6);

	M_CreateSmallVerChain_P1(0, 8);
	M_CreateSmallVerChain_P1(6, 8);

	M_CreateSmallVerChain_P1(1, 9);
	M_CreateSmallVerChain_P1(5, 9);

	M_CreateSmallVerChain_P1(2, 10);
	M_CreateSmallVerChain_P1(4, 10);

	M_CreateSmallVerChain_P1(3, 11);

	M_CreateSmallVerChain_P1(2, 12);
	M_CreateSmallVerChain_P1(4, 12);

	M_CreateSmallVerChain_P1(1, 13);
	M_CreateSmallVerChain_P1(5, 13);

	M_CreateSmallVerChain_P1(0, 14);
	M_CreateSmallVerChain_P1(6, 14);

	M_CreateSmallVerChain_P1(0, 16);
	M_CreateSmallVerChain_P1(6, 16);

	M_CreateSmallVerChain_P1(1, 17);
	M_CreateSmallVerChain_P1(5, 17);

	M_CreateSmallVerChain_P1(2, 18);
	M_CreateSmallVerChain_P1(4, 18);

	M_CreateSmallVerChain_P1(3, 19);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(6, 21);
	M_CreateSmallHorChain_P1(0, 21);
	M_CreateSmallHorChain_P1(4, 21);

	M_CreateSmallVerChain_P1(1, 22);
	M_CreateSmallVerChain_P1(5, 22);
	M_CreateSmallHorChain_P1(1, 22);
	M_CreateSmallHorChain_P1(3, 22);

	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallHorChain_P1(2, 23);

	M_CreateSmallVerChain_P1(2, 24);
	M_CreateSmallVerChain_P1(4, 24);
	M_CreateSmallHorChain_P1(0, 24);
	M_CreateSmallHorChain_P1(4, 24);

	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallHorChain_P1(1, 25);
	M_CreateSmallHorChain_P1(3, 25);

	M_CreateSmallVerChain_P1(2, 26);
	M_CreateSmallVerChain_P1(3, 26);
	M_CreateSmallVerChain_P1(4, 26);

	M_CreateSmallVerChain_P1(0, 27);
	M_CreateSmallVerChain_P1(6, 27);
	M_CreateSmallHorChain_P1(0, 27);
	M_CreateSmallHorChain_P1(4, 27);

	M_CreateSmallVerChain_P1(0, 28);
	M_CreateSmallVerChain_P1(1, 28);
	M_CreateSmallVerChain_P1(5, 28);
	M_CreateSmallVerChain_P1(6, 28);
	M_CreateSmallHorChain_P1(2, 28);

	M_CreateSmallVerChain_P1(0, 29);
	M_CreateSmallVerChain_P1(1, 29);
	M_CreateSmallVerChain_P1(2, 29);
	M_CreateSmallVerChain_P1(4, 29);
	M_CreateSmallVerChain_P1(5, 29);
	M_CreateSmallVerChain_P1(6, 29);
}								 

void SinChapter4::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 0);
	M_CreateHitChain(ESinHitChainType::Left, 2);
	M_CreateHitChain(ESinHitChainType::Right, 0);
	M_CreateHitChain(ESinHitChainType::Right, 2);
	M_CreateHitChainHp("������ �罽");

	M_SetSmallChainVecSize(4, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(6, 0);

	M_CreateSmallHorChain_P2(0, 1);
	M_CreateSmallHorChain_P2(4, 1);

	M_CreateSmallVerChain_P2(1, 2);
	M_CreateSmallVerChain_P2(5, 2);
	M_CreateSmallHorChain_P2(0, 2);
	M_CreateSmallHorChain_P2(3, 2);

	M_CreateSmallVerChain_P2(2, 3);
	M_CreateSmallVerChain_P2(4, 3);
	M_CreateSmallHorChain_P2(1, 3);
	M_CreateSmallHorChain_P2(4, 3);
}

void SinChapter4::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();

	C_SpawnDialogue(1);

	FVector Scale = { 0.558f, 0.693f };
	FVector Pos = { 0.0f, -0.0402f };
	C_SpawnJudge("Jud_Intro_004.png", SinChap4_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap4_Script[1]);
}

void SinChapter4::Enter(float _DeltaTime)
{
	SinCutSceneManager::Enter(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_StateChange(ESinSceneState::Select);
	}
}

void SinChapter4::SelectStart()
{
	SinCutSceneManager::SelectStart();

	C_MenubarTextSet(0, SinChap4_Script[2]);
	C_MenubarTextSet(1, SinChap4_Script[3]);
	OrderCount = 0;
}

void SinChapter4::SelectMenu()
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
	case 4:
		Select5();
		break;
	case 5:
		Select6();
		break;
	case 6:
		Select7();
		break;
	case 7:
		Select8();
		break;
	case 8:
		Select9();
		break;
	case 9:
		Select10();
		break;
	case 10:
		Select11();
		break;
	case 11:
		Select12();
		break;	
	case 12:
		Select13();
		break;
	case 13:
		Select14();
		break;
	}
}

void SinChapter4::Success(float _DeltaTime)
{
	SinCutSceneManager::Success(_DeltaTime);

	switch (OrderCount)
	{
	case 0:
		Success1();
		break;
	case 1:
		Success2();
		break;
	}
}

void SinChapter4::Select1()
{
	C_MenubarRenderActiveOff();
	C_BooperTextSet(SinChap4_Script[4]);
	C_GetBooper()->GetImageRenderer()->ActiveOn();

	++OrderCount;
}

void SinChapter4::Select2()
{
	C_MenubarRenderActiveOn();
	C_MenubarTextSet(0, SinChap4_Script[5]);
	C_MenubarTextSet(1, SinChap4_Script[6]);
	C_GetBooper()->GetImageRenderer()->ActiveOff();

	++OrderCount;
}

void SinChapter4::Select3()
{
	FVector Scale = { 0.466f, 0.693f };
	FVector Pos = { 0.0f, -0.042f };
	C_JudgeChange("Jud_Resign.png", Pos, Scale);

	C_MenubarRenderActiveOff();
	C_BooperTextSet(SinChap4_Script[7]);
	C_GetBooper()->GetImageRenderer()->ActiveOn();

	++OrderCount;
}

void SinChapter4::Select4()
{
	C_BooperTextSet(SinChap4_Script[8]);
	++OrderCount;
}

void SinChapter4::Select5()
{
	C_BooperTextSet(SinChap4_Script[9]);
	++OrderCount;
}

void SinChapter4::Select6()
{
	FVector Scale = { 0.558f, 0.693f };
	FVector Pos = { 0.0f, -0.0402f };
	C_JudgeChange("Jud_Intro_004.png", Pos, Scale);
	C_BooperTextSet(SinChap4_Script[10]);
	++OrderCount;
}

void SinChapter4::Select7()
{
	C_BooperTextSet(SinChap4_Script[11]);
	++OrderCount;
}

void SinChapter4::Select8()
{
	C_BooperTextSet(SinChap4_Script[12]);
	++OrderCount;
}

void SinChapter4::Select9()
{
	C_BooperTextSet(SinChap4_Script[13]);
	++OrderCount;
}

void SinChapter4::Select10()
{
	FVector Scale = { 0.4666f, 0.692f };
	FVector Pos = { 0.0f, -0.042f };
	C_JudgeChange("Jud_Angry.png", Pos, Scale);

	C_BooperTextSet(SinChap4_Script[14]);
	++OrderCount;
}

void SinChapter4::Select11()
{
	C_BooperTextSet(SinChap4_Script[15]);
	++OrderCount;
}

void SinChapter4::Select12()
{
	FVector Scale = { 0.466f, 0.693f };
	FVector Pos = { 0.0f, -0.042f };
	C_JudgeChange("Jud_Resign.png", Pos, Scale);

	C_BooperTextSet(SinChap4_Script[16]);
	++OrderCount;
}

void SinChapter4::Select13()
{
	C_MenubarRenderActiveOn();
	C_MenubarTextSet(0, SinChap4_Script[17]);
	C_MenubarTextSet(1, SinChap4_Script[18]);
	C_GetBooper()->GetImageRenderer()->ActiveOff();

	++OrderCount;
}

void SinChapter4::Select14()
{
	FVector Scale = { 0.466f, 0.693f };
	FVector Pos = { 0.0f, -0.042f };
	C_JudgeChange("Jud_Shock.png", Pos, Scale);
	C_BooperTextSet(SinChap4_Script[19]);

	OrderCount = 0;
	C_StateChange(ESinSceneState::Success);
}

void SinChapter4::Success1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(SinChap4_Script[20]);

		FVector WinScale = ContentsHelper::GetWindowScale();
		C_GetBooper()->GetImageRenderer()->ChangeAnimation("Booper_Idle");
		C_GetBooper()->GetImageRenderer()->SetTransform({ {0, 0}, { WinScale.X * 0.027f, WinScale.Y * 0.022f } });

		++OrderCount;
	}
}

void SinChapter4::Success2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		SuccessEnd();
	}
}

void SinChapter4::ChangeChapter()
{
	SinManager::ChangeChapter();
	
	CreateChapter<EpilogueOpening>("EpilogueOpening");
	GEngine->ChangeLevel("EpilogueOpening");
}



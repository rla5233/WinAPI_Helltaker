#include "SinChapter3.h"

#include "Sin_Judge.h"

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
	M_CreateHitChainHp("������ �罽");

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

	FVector Scale = { 0.416f, 0.693f };
	FVector Pos = { 0.0f, -0.0502f };
	C_SpawnJudge("Jud_Laugh.png", SinChap3_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap3_Script[1]);
}

void SinChapter3::EnterStart()
{

}

void SinChapter3::Enter(float _DeltaTime)
{
}

void SinChapter3::ChangeChapter()
{}

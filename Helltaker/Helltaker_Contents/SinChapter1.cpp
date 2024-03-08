#include "SinChapter1.h"

#include "Sin_Judge.h"

bool SinChapter1::IsLoad = false;
const std::vector<const char*> SinChapter1::SinChap1_Script =
{
	/* 0  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 1  Script 1  */ "ħ���ھ�, �˾��� ��谡 ������ �����?",
	/* 2  Script 2  */ "�̸� �����ϰ� ��������!",
	/* 3  Script 3  */ "����� ������! �� �༮�� ����� �̹� ��������!",
	/* 4  Script 4  */ "�����϶�! ���� ��¥ �����̴�!",

	/* 5  Demon	    */ "�� �ֵ��� �Ǹ� �ɸ����ν�",
	/* 6  Script 1  */ "�ȵ�, �������� ��! �츱 ������ ��������!",

	/* 7  Demon	    */ "�ǰ��� �Ǹ� �ǵ����ī",
	/* 8  Script 1  */ "�׸��� Ŀ�ǵ� Ÿ �ּž���.",

	/* 9  Demon	    */ "������ CEO �����",
	/* 10 Script 1  */ "�̷�, ������Ʈ. �� �༮�� �𸣰� �ְ�����, �� �ž�. �׳�\n������ �� ���� ����?",
};

SinChapter1::SinChapter1()
{
}

SinChapter1::~SinChapter1()
{
}

void SinChapter1::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters\\Jud_Intro", "Jud_Intro_004.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Back.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Angry.png");

		AddChapterSet("SinChapter1");
		IsLoad = true;
	}
}

void SinChapter1::LevelStart(ULevel* _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(1);

	M_StateChange(ESinState::Intro);
}

void SinChapter1::Phase1_Start()
{
	SinChapterManager::Phase1_Start();

	M_SetSmallChainVecSize(26, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(0, 0);
	M_CreateSmallVerChain_P1(1, 1);
	M_CreateSmallVerChain_P1(2, 2);
	M_CreateSmallVerChain_P1(3, 3);
	M_CreateSmallVerChain_P1(4, 4);
	M_CreateSmallVerChain_P1(6, 6);
	M_CreateSmallVerChain_P1(5, 7);
	M_CreateSmallVerChain_P1(4, 8);
	M_CreateSmallVerChain_P1(3, 9);
	M_CreateSmallVerChain_P1(2, 10);
	M_CreateSmallVerChain_P1(0, 12);
	M_CreateSmallVerChain_P1(2, 13);
	M_CreateSmallVerChain_P1(4, 14);
	M_CreateSmallVerChain_P1(1, 15);
	M_CreateSmallVerChain_P1(6, 15);
	M_CreateSmallVerChain_P1(0, 16);
	M_CreateSmallVerChain_P1(3, 16);
	M_CreateSmallVerChain_P1(2, 17);
	M_CreateSmallVerChain_P1(5, 17);
	M_CreateSmallVerChain_P1(4, 18);
	M_CreateSmallVerChain_P1(6, 19);
	M_CreateSmallVerChain_P1(3, 21);
	M_CreateSmallVerChain_P1(0, 22);
	M_CreateSmallVerChain_P1(6, 22);
	M_CreateSmallVerChain_P1(2, 23);
	M_CreateSmallVerChain_P1(4, 23);
	M_CreateSmallVerChain_P1(1, 24);
	M_CreateSmallVerChain_P1(5, 24);
	M_CreateSmallVerChain_P1(0, 25);
	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallVerChain_P1(6, 25);
}

void SinChapter1::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 1);
	M_CreateHitChain(ESinHitChainType::Right, 1);
	M_CreateHitChainHp("������ �罽");
}

void SinChapter1::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();
	
	C_SpawnDialogue(1);

	FVector Scale = { 0.558f, 0.693f };
	FVector Pos = { 0.0f, -0.0402f };
	C_SpawnJudge("Jud_Intro_004.png", SinChap1_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap1_Script[1]);
}

void SinChapter1::CutScene(float _DeltaTime)
{}

void SinChapter1::EnterStart()
{}

void SinChapter1::Enter(float _DeltaTime)
{}

void SinChapter1::EndStart()
{}

void SinChapter1::ChangeChapter()
{}
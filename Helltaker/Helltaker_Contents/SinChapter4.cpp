#include "SinChapter4.h"

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


}

void SinChapter4::EnterStart()
{
}

void SinChapter4::Enter(float _DeltaTime)
{
}

void SinChapter4::SelectStart()
{
}

void SinChapter4::SelectMenu()
{
}

void SinChapter4::ChangeChapter()
{
	SinManager::ChangeChapter();

}

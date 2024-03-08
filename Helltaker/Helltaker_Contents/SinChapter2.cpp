#include "SinChapter2.h"

bool SinChapter2::IsLoad = false;
const std::vector<const char*> SinChapter2::SinChap1_Script =
{
	
};

SinChapter2::SinChapter2()
{
}

SinChapter2::~SinChapter2()
{
}

void SinChapter2::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{

		AddChapterSet("SinChapter2");

		IsLoad = true;
	}
}

void SinChapter2::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(2);

	M_StateChange(ESinState::Intro);
}

void SinChapter2::Phase1_Start()
{
	SinChapterManager::Phase1_Start();

	M_SetSmallChainVecSize(25, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(0, 0);
	M_CreateSmallVerChain_P1(3, 0);
	M_CreateSmallVerChain_P1(6, 0);

	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);

	M_CreateSmallVerChain_P1(3, 2);

	M_CreateSmallVerChain_P1(2, 3);
	M_CreateSmallVerChain_P1(4, 3);

	M_CreateSmallVerChain_P1(0, 4);
	M_CreateSmallVerChain_P1(3, 4);
	M_CreateSmallVerChain_P1(6, 4);

	M_CreateSmallHorChain_P1(4, 6);

	M_CreateSmallHorChain_P1(2, 7);

	M_CreateSmallHorChain_P1(0, 8);
	M_CreateSmallHorChain_P1(4, 8);

	M_CreateSmallHorChain_P1(2, 9);

	M_CreateSmallHorChain_P1(0, 10);

	M_CreateSmallVerChain_P1(0, 11);
	M_CreateSmallVerChain_P1(6, 11);

	M_CreateSmallVerChain_P1(0, 12);
	M_CreateSmallVerChain_P1(1, 12);
	M_CreateSmallVerChain_P1(5, 12);
	M_CreateSmallVerChain_P1(6, 12);

	M_CreateSmallVerChain_P1(3, 13);

	M_CreateSmallVerChain_P1(2, 14);
	M_CreateSmallVerChain_P1(3, 14);
	M_CreateSmallVerChain_P1(4, 14);

	M_CreateSmallVerChain_P1(0, 15);
	M_CreateSmallVerChain_P1(2, 15);
	M_CreateSmallVerChain_P1(4, 15);
	M_CreateSmallVerChain_P1(6, 15);

	M_CreateSmallVerChain_P1(1, 16);
	M_CreateSmallVerChain_P1(3, 16);
	M_CreateSmallVerChain_P1(5, 16);

	M_CreateSmallVerChain_P1(0, 17);
	M_CreateSmallVerChain_P1(6, 17);

	M_CreateSmallVerChain_P1(2, 18);
	M_CreateSmallVerChain_P1(4, 18);

	M_CreateSmallVerChain_P1(1, 19);
	M_CreateSmallVerChain_P1(3, 19);
	M_CreateSmallVerChain_P1(5, 19);

	M_CreateSmallVerChain_P1(0, 20);
	M_CreateSmallVerChain_P1(6, 20);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(1, 21);
	M_CreateSmallVerChain_P1(3, 21);
	M_CreateSmallVerChain_P1(5, 21);
	M_CreateSmallVerChain_P1(6, 21);

	M_CreateSmallVerChain_P1(2, 22);
	M_CreateSmallVerChain_P1(4, 22);

	M_CreateSmallVerChain_P1(1, 23);
	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallVerChain_P1(5, 23);

	M_CreateSmallVerChain_P1(0, 24);
	M_CreateSmallVerChain_P1(3, 24);
	M_CreateSmallVerChain_P1(6, 24);
}

void SinChapter2::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 2);
	M_CreateHitChain(ESinHitChainType::Right, 0);
	M_CreateHitChainHp("Å½¿åÀÇ »ç½½");

	M_SetSmallChainVecSize(3, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(6, 0);

	M_CreateSmallVerChain_P2(1, 1);
	M_CreateSmallVerChain_P2(5, 1);

	M_CreateSmallVerChain_P2(2, 2);
	M_CreateSmallVerChain_P2(4, 2);
}

void SinChapter2::CutSceneStart()
{}

void SinChapter2::EnterStart()
{}

void SinChapter2::Enter(float _DeltaTime)
{}

void SinChapter2::ChangeChapter()
{}

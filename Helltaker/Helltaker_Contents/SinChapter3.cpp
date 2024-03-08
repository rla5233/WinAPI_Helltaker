#include "SinChapter3.h"

#include "Sin_Judge.h"

bool SinChapter3::IsLoad = false;
const std::vector<const char*> SinChapter3::SinChap3_Script =
{
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
}

void SinChapter3::CutSceneStart()
{
}

void SinChapter3::EnterStart()
{
}

void SinChapter3::Enter(float _DeltaTime)
{
}

void SinChapter3::ChangeChapter()
{}

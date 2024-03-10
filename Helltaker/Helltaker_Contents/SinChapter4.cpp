#include "SinChapter4.h"

bool SinChapter4::IsLoad = false;
const std::vector<const char*> SinChapter4::SinChap4_Script =
{
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
}

void SinChapter4::Phase2_Start()
{
}

void SinChapter4::CutSceneStart()
{
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

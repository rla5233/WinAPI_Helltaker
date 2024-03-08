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
}

void SinChapter2::Phase1_Start()
{}

void SinChapter2::Phase2_Start()
{}

void SinChapter2::CutSceneStart()
{}

void SinChapter2::EnterStart()
{}

void SinChapter2::Enter(float _DeltaTime)
{}

void SinChapter2::ChangeChapter()
{}

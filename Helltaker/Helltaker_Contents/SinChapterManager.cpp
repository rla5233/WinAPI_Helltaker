#include "SinChapterManager.h"

#include "BackGround.h"

bool SinChapterManager::IsLoad = false;

const int SinChapterManager::SinPitCount = 3;

SinChapterManager::SinChapterManager()
{
}

SinChapterManager::~SinChapterManager()
{
}

void SinChapterManager::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "SinBG.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pit.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinBG(std::string_view _Name)
{
	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	SinBG->CreateBackGround(_Name);
	SinBG->SetOrder(static_cast<int>(SinRenderOrder::BackGround));
	SinBG->GetImageRenderer()->SetAlpha(0.8f);

	AllSMapActors[reinterpret_cast<__int64>(SinBG)] = SinBG;
}

void SinChapterManager::M_CreateSinPit()
{
	for (int i = 0; i < SinPitCount; i++)
	{
		SinPit.push_back(SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround)));
		SinPit[i]->CreateImageRenderer()
	}
}

void SinChapterManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void SinChapterManager::LevelStart(ULevel* _PrevLevel)
{
}

void SinChapterManager::LevelEnd(ULevel* _NextLevel)
{
}

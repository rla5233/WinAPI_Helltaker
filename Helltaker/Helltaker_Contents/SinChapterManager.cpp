#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"

bool SinChapterManager::IsLoad = false;

const int SinChapterManager::SinPitCount = 3;
const FVector SinChapterManager::SinPitInterval = { 0.0f, 0.6079f };

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
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pit_Left.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pit_Right.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinBG(std::string_view _Name)
{
	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	SinBG->CreateBackGround(_Name, EBackGroundType::Sin);
	SinBG->GetImageRenderer()->SetAlpha(0.75f);

	AllSMapActors[reinterpret_cast<__int64>(SinBG)] = SinBG;
}

void SinChapterManager::M_CreateSinPit()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.283f, WinScale.Y * 0.607f };
	FVector Pos = { WinScale.X * 0.359f, WinScale.Y * 0.196f };

	for (int i = 0; i < SinPitCount; i++)
	{		
		SinPit.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::BackGround)));
		SinPit[i]->SetActorLocation({ WinScale.hX(), Pos.Y  });

		SinPit[i]->CreateImageRenderer("Left_Pit", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Left_Pit")->SetImage("Sin_Pit_Left.png");
		SinPit[i]->GetImageRenderer("Left_Pit")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinPit[i]->CreateImageRenderer("Right_Pit", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Right_Pit")->SetImage("Sin_Pit_Right.png");
		SinPit[i]->GetImageRenderer("Right_Pit")->SetTransform({ { Pos.X, 0.0f }, Scale });

		Pos += WinScale * SinPitInterval;
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

#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"

bool SinChapterManager::IsLoad = false;

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

		ContentsHelper::LoadImg("Chapter\\Component\\SinGear", "L_SinGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\SinGear", "R_SinGears_001.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinBG(std::string_view _Name)
{
	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	SinBG->CreateBackGround(_Name, EBackGroundType::Sin);
	SinBG->GetImageRenderer()->SetAlpha(0.7f);

	AllSMapActors[reinterpret_cast<__int64>(SinBG)] = SinBG;
}

void SinChapterManager::M_CreateSinPit()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.283f, WinScale.Y * 0.607f };
	FVector Pos = { WinScale.X * 0.359f, WinScale.Y * 0.196f };

	for (int i = 0; i < 3; i++)
	{		
		SinPit.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::UnderBackGround)));
		SinPit[i]->SetActorLocation({ WinScale.hX(), Pos.Y  });

		SinPit[i]->CreateImageRenderer("Left", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Left")->SetImage("Sin_Pit_Left.png");
		SinPit[i]->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinPit[i]->CreateImageRenderer("Right", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Right")->SetImage("Sin_Pit_Right.png");
		SinPit[i]->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

		Pos += WinScale * SinPitInterval;

		AllSMapActors[reinterpret_cast<__int64>(SinPit[i])] = SinPit[i];
	}
}

void SinChapterManager::M_CreateSinGear()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.208f, WinScale.Y * 0.278f };
	FVector Pos = { WinScale.X * 0.396f, WinScale.Y * 0.861f };

	for (int i = 0; i < 2; i++)
	{
		SinGear.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Bottom)));
		SinGear[i]->SetActorLocation({ WinScale.hX(), Pos.Y });

		SinGear[i]->CreateImageRenderer("Left", SinRenderOrder::Bottom);
		SinGear[i]->GetImageRenderer("Left")->SetImage("L_SinGears_001.png");
		SinGear[i]->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinGear[i]->CreateImageRenderer("Right", SinRenderOrder::Bottom);
		SinGear[i]->GetImageRenderer("Right")->SetImage("R_SinGears_001.png");
		SinGear[i]->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

		AllSMapActors[reinterpret_cast<__int64>(SinGear[i])] = SinGear[i];
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

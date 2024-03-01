#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"

bool SinChapterManager::IsLoad = false;

const float SinChapterManager::SinPitInterval = 0.6079f;

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
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LPit.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RPit.png");

		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_LGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_RGears_001.png");
		
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LPanel.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RPanel.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Eye.png");

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
		SinPit[i]->GetImageRenderer("Left")->SetImage("Sin_LPit.png");
		SinPit[i]->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinPit[i]->CreateImageRenderer("Right", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Right")->SetImage("Sin_RPit.png");
		SinPit[i]->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

		Pos.Y += WinScale.Y * SinPitInterval;

		AllSMapActors[reinterpret_cast<__int64>(SinPit[i])] = SinPit[i];
	}
}

void SinChapterManager::M_CreateSinGear()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.208f, WinScale.Y * 0.278f };
	FVector Pos = { WinScale.X * 0.396f, WinScale.Y * 0.861f };

	SinGear = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Bottom));
	SinGear->SetActorLocation({ WinScale.hX(), Pos.Y });
	
	SinGear->CreateImageRenderer("Left", SinRenderOrder::Bottom);
	SinGear->GetImageRenderer("Left")->SetImage("Sin_LGears_001.png");
	SinGear->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });
	
	SinGear->CreateImageRenderer("Right", SinRenderOrder::Bottom);
	SinGear->GetImageRenderer("Right")->SetImage("Sin_RGears_001.png");
	SinGear->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });
	
	AllSMapActors[reinterpret_cast<__int64>(SinGear)] = SinGear;
}

void SinChapterManager::M_CreateSinPanel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.39f, WinScale.Y * 0.133f };
	FVector Pos = { WinScale.X * 0.228f, WinScale.Y * 0.962f };

	SinComponent* SinPanel = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid));
	SinPanel->SetActorLocation({ WinScale.hX(), Pos.Y });

	SinPanel->CreateImageRenderer("Left", SinRenderOrder::Mid);
	SinPanel->GetImageRenderer("Left")->SetImage("Sin_LPanel.png");
	SinPanel->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

	SinPanel->CreateImageRenderer("Right", SinRenderOrder::Mid);
	SinPanel->GetImageRenderer("Right")->SetImage("Sin_RPanel.png");
	SinPanel->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

	SinPanel->CreateImageRenderer("Eye", SinRenderOrder::Mid);
	SinPanel->GetImageRenderer("Eye")->SetImage("Sin_Eye.png");
	SinPanel->GetImageRenderer("Eye")->SetTransform({ { Pos.X, 0.0f }, Scale });

	AllSMapActors[reinterpret_cast<__int64>(SinPanel)] = SinPanel;
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

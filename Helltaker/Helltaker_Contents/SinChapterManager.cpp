#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"

bool SinChapterManager::IsLoad = false;

const float SinChapterManager::SinPitInterval = 0.6079f;
const float SinChapterManager::SinFireInter = 0.06f;

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
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pyre_On.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Pyre_Off.png");
		ContentsHelper::LoadFolder("Chapter\\Component", "Sin_Fire");

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LShield.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RShield.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LShield_Top.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RShield_Top.png");

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Bridge.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinBackGround()
{
	M_CreateSinBG("SinBG");
	M_CreateSinPit();
	M_CreateSinGear();
}

void SinChapterManager::M_CreateSinBG(std::string_view _Name)
{
	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	SinBG->CreateBackGround(_Name, EBackGroundType::Sin);

	AllSMapActors[reinterpret_cast<__int64>(SinBG)] = SinBG;
}

void SinChapterManager::M_CreateSinPit()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.283f, WinScale.Y * 0.607f };
	FVector Pos = { WinScale.X * 0.359f, WinScale.Y * 0.196f };

	SinPit.reserve(3);
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

void SinChapterManager::M_CreateSinUnderPanel()
{
	M_CreateSinPanel();
	M_CreateSinPyre();
}

void SinChapterManager::M_CreateSinPanel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.39f, WinScale.Y * 0.133f };
	FVector Pos = { WinScale.X * 0.228f, WinScale.Y * 0.962f };
	FVector EyeScale = { WinScale.X * 0.167f, WinScale.Y * 0.167f };
	float EyePosY = WinScale.Y * (-0.005f);

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
	SinPanel->GetImageRenderer("Eye")->SetTransform({ { 0.0f, EyePosY }, EyeScale });

	AllSMapActors[reinterpret_cast<__int64>(SinPanel)] = SinPanel;
}

void SinChapterManager::M_CreateSinPyre()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector PyreScale = { WinScale.X * 0.13f, WinScale.Y * 0.111f };
	FVector Pos = { WinScale.X * 0.255f, WinScale.Y * 0.962f };
	const float IntervalX = WinScale.X * 0.111f;

	FVector FireScale = { WinScale.X * 0.0625f, WinScale.Y * 0.107f };
	float FirePosY = WinScale.Y * (-0.035f);

	int idx = 0;
	SinPyre.reserve(4);
	for (int i = 0; i < 2; i++)
	{
		SinPyre.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Top)));
		SinPyre[idx]->SetActorLocation({ Pos.X + (IntervalX * i), Pos.Y });

		SinPyre[idx]->CreateImageRenderer("Pyre", SinRenderOrder::Top);
		SinPyre[idx]->GetImageRenderer("Pyre")->SetImage("Sin_Pyre_On.png");
		SinPyre[idx]->GetImageRenderer("Pyre")->SetTransform({ { 0.0f, 0.0f }, PyreScale });

		SinPyre[idx]->CreateImageRenderer("Fire", SinRenderOrder::Top);
		SinPyre[idx]->GetImageRenderer("Fire")->SetImage("Sin_Fire");
		SinPyre[idx]->GetImageRenderer("Fire")->SetTransform({ { 0.0f, FirePosY }, FireScale });
		SinPyre[idx]->GetImageRenderer("Fire")->CreateAnimation("Sin_Fire", "Sin_Fire", 0, 11, SinFireInter, true);
		SinPyre[idx]->GetImageRenderer("Fire")->ChangeAnimation("Sin_Fire");

		AllSMapActors[reinterpret_cast<__int64>(SinPyre[idx])] = SinPyre[idx];
		++idx;
	}
	
	Pos.X = WinScale.X * 0.635f;
	for (int i = 0; i < 2; i++)
	{
		SinPyre.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Top)));
		SinPyre[idx]->SetActorLocation({ Pos.X + (IntervalX * i), Pos.Y });

		SinPyre[idx]->CreateImageRenderer("Pyre", SinRenderOrder::Top);
		SinPyre[idx]->GetImageRenderer("Pyre")->SetImage("Sin_Pyre_On.png");
		SinPyre[idx]->GetImageRenderer("Pyre")->SetTransform({ { 0.0f, 0.0f }, PyreScale });

		SinPyre[idx]->CreateImageRenderer("Fire", SinRenderOrder::Top);
		SinPyre[idx]->GetImageRenderer("Fire")->SetImage("Sin_Fire");
		SinPyre[idx]->GetImageRenderer("Fire")->SetTransform({ { 0.0f, FirePosY }, FireScale });
		SinPyre[idx]->GetImageRenderer("Fire")->CreateAnimation("Sin_Fire", "Sin_Fire", 0, 11, SinFireInter, true);
		SinPyre[idx]->GetImageRenderer("Fire")->ChangeAnimation("Sin_Fire");

		AllSMapActors[reinterpret_cast<__int64>(SinPyre[idx])] = SinPyre[idx];
		++idx;
	}
}

void SinChapterManager::M_CreateSinShield()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.406f, WinScale.Y * 0.686f };
	FVector Pos = { WinScale.X * 0.177f, WinScale.Y * 0.322f };

	FVector TopScale = { WinScale.X * 0.2786f, WinScale.Y * 0.296f };
	FVector TopPos = { WinScale.X * 0.1132f, WinScale.Y * (-0.1949f) };

	SinComponent* SinShield = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid));
	SinShield->SetActorLocation({ WinScale.hX(), Pos.Y });
	SinShield->CreateImageRenderer("LShield", SinRenderOrder::Mid);
	SinShield->GetImageRenderer("LShield")->SetImage("Sin_LShield.png");
	SinShield->GetImageRenderer("LShield")->SetTransform({ { -Pos.X, 0.0f },  Scale });

	SinShield->SetActorLocation({ WinScale.hX(), Pos.Y });
	SinShield->CreateImageRenderer("RShield", SinRenderOrder::Mid);
	SinShield->GetImageRenderer("RShield")->SetImage("Sin_RShield.png");
	SinShield->GetImageRenderer("RShield")->SetTransform({ { Pos.X, 0.0f },  Scale });

	SinShield->CreateImageRenderer("LShield_Top", SinRenderOrder::Top);
	SinShield->GetImageRenderer("LShield_Top")->SetImage("Sin_LShield_Top.png");
	SinShield->GetImageRenderer("LShield_Top")->SetTransform({ { -TopPos.X, TopPos.Y },  TopScale });

	SinShield->CreateImageRenderer("RShield_Top", SinRenderOrder::Top);
	SinShield->GetImageRenderer("RShield_Top")->SetImage("Sin_RShield_Top.png");
	SinShield->GetImageRenderer("RShield_Top")->SetTransform({ { TopPos.X, TopPos.Y },  TopScale });

	AllSMapActors[reinterpret_cast<__int64>(SinShield)] = SinShield;
}

void SinChapterManager::M_CreateSinBridge()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.492f, WinScale.Y * 0.556f };
	FVector Pos = { WinScale.hX(), WinScale.Y * 0.322f };
	const float IntervalY = Scale.Y;

	SinBridge.reserve(1);
	for (int i = 0; i < 1; i++)
	{
		SinBridge.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid)));
		SinBridge[i]->SetActorLocation(Pos);
		SinBridge[i]->CreateImageRenderer("Bridge", SinRenderOrder::Mid);
		SinBridge[i]->GetImageRenderer("Bridge")->SetImage("Sin_Bridge.png");
		SinBridge[i]->GetImageRenderer("Bridge")->SetTransform({ { 0.0f, 0.0f },  Scale });
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

#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"

bool SinChapterManager::IsLoad = false;

const float SinChapterManager::SinFireInter = 0.06f;

const FVector SinChapterManager::SinPitScale = { 0.283f, 0.6074f };
const float SinChapterManager::SinPitSpeedY = -50.0f;

const FVector SinChapterManager::SinBridgeScale = { 0.4912f, 0.5555f };
const float SinChapterManager::SinBridgeSpeedY = -180.0f;

const FVector SinChapterManager::SinChainSCale = { 0.0375f, 0.1388f };
const float SinChapterManager::SinChainSpeedY = -180.0f;

const FVector SinChapterManager::ThornScale = { 0.0479f, 0.0851f };

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

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Skull_001.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Skull_002.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LArm.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RArm.png");
		
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LChainLink.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RChainLink.png");

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Bridge.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinMap()
{
	M_CreateSinBG("SinBG");
	M_CreateSinPit();
	M_CreateSinGear();
	M_CreateSinPanel();
	M_CreateSinPyre();
	M_CreateSinShield();
	M_CreateSinBridge();
	M_CreateThorn();
	M_CreateSinSkull();
	M_CreateSinChain();
	M_CreateSinPiston();
}

void SinChapterManager::M_CreateSinBG(std::string_view _Name)
{
	BackGround* SinBG = SpawnActor<BackGround>(static_cast<int>(SinUpdateOrder::BackGround));
	SinBG->CreateBackGround(_Name, EBackGroundType::Sin);

	AllMapRenderActors.push_back(SinBG);
}

void SinChapterManager::M_CreateSinPit()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * SinPitScale;
	FVector Pos = { WinScale.X * 0.359f, WinScale.Y * 0.304f };

	SinPit.reserve(3);
	for (int i = 0; i < 3; i++)
	{		
		SinPit.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::UnderBackGround)));
		SinPit[i]->SetActorLocation({WinScale.hX(), Pos.Y});

		SinPit[i]->CreateImageRenderer("Left", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Left")->SetImage("Sin_LPit.png");
		SinPit[i]->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinPit[i]->CreateImageRenderer("Right", SinRenderOrder::UnderBackGround);
		SinPit[i]->GetImageRenderer("Right")->SetImage("Sin_RPit.png");
		SinPit[i]->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });
		
		Pos.Y += Scale.Y;

		AllMapRenderActors.push_back(SinPit[i]);
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
	
	AllMapRenderActors.push_back(SinGear);
}

void SinChapterManager::M_CreateSinPanel()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.39f, WinScale.Y * 0.133f };
	FVector Pos = { WinScale.X * 0.228f, WinScale.Y * 0.962f };
	FVector EyeScale = { WinScale.X * 0.167f, WinScale.Y * 0.167f };
	float EyePosY = WinScale.Y * (-0.005f);

	SinComponent* SinPanel = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Top));
	SinPanel->SetActorLocation({ WinScale.hX(), Pos.Y });

	SinPanel->CreateImageRenderer("Left", SinRenderOrder::Top);
	SinPanel->GetImageRenderer("Left")->SetImage("Sin_LPanel.png");
	SinPanel->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

	SinPanel->CreateImageRenderer("Right", SinRenderOrder::Top);
	SinPanel->GetImageRenderer("Right")->SetImage("Sin_RPanel.png");
	SinPanel->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

	SinPanel->CreateImageRenderer("Eye", SinRenderOrder::Top);
	SinPanel->GetImageRenderer("Eye")->SetImage("Sin_Eye.png");
	SinPanel->GetImageRenderer("Eye")->SetTransform({ { 0.0f, EyePosY }, EyeScale });

	AllMapRenderActors.push_back(SinPanel);
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

		AllMapRenderActors.push_back(SinPyre[idx]);
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

		AllMapRenderActors.push_back(SinPyre[idx]);
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
	SinShield->CreateImageRenderer("LShield", SinRenderOrder::Bottom);
	SinShield->GetImageRenderer("LShield")->SetImage("Sin_LShield.png");
	SinShield->GetImageRenderer("LShield")->SetTransform({ { -Pos.X, 0.0f },  Scale });

	SinShield->SetActorLocation({ WinScale.hX(), Pos.Y });
	SinShield->CreateImageRenderer("RShield", SinRenderOrder::Bottom);
	SinShield->GetImageRenderer("RShield")->SetImage("Sin_RShield.png");
	SinShield->GetImageRenderer("RShield")->SetTransform({ { Pos.X, 0.0f },  Scale });

	SinShield->CreateImageRenderer("LShield_Top", SinRenderOrder::Top);
	SinShield->GetImageRenderer("LShield_Top")->SetImage("Sin_LShield_Top.png");
	SinShield->GetImageRenderer("LShield_Top")->SetTransform({ { -TopPos.X, TopPos.Y },  TopScale });

	SinShield->CreateImageRenderer("RShield_Top", SinRenderOrder::Top);
	SinShield->GetImageRenderer("RShield_Top")->SetImage("Sin_RShield_Top.png");
	SinShield->GetImageRenderer("RShield_Top")->SetTransform({ { TopPos.X, TopPos.Y },  TopScale });

	AllMapRenderActors.push_back(SinShield);
}

void SinChapterManager::M_CreateSinSkull()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector SkullScale = { WinScale.X * 0.212f, WinScale.Y * 0.396f };
	FVector SkullPos = { WinScale.X * 0.412f, WinScale.Y * 0.665f };

	Skull = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Top));
	Skull->SetActorLocation({ WinScale.hX(), SkullPos.Y });

	Skull->CreateImageRenderer("LSkull_Bottom", SinRenderOrder:: Mid);
	Skull->GetImageRenderer("LSkull_Bottom")->SetImage("Sin_Skull_001.png");
	Skull->GetImageRenderer("LSkull_Bottom")->SetTransform({ { -SkullPos.X, 0.0f },  SkullScale });

	Skull->CreateImageRenderer("RSkull_Bottom", SinRenderOrder::Mid);
	Skull->GetImageRenderer("RSkull_Bottom")->SetImage("Sin_Skull_001.png");
	Skull->GetImageRenderer("RSkull_Bottom")->SetTransform({ { SkullPos.X, 0.0f },  SkullScale });

	Skull->CreateImageRenderer("LSkull_Top", SinRenderOrder::Top);
	Skull->GetImageRenderer("LSkull_Top")->SetImage("Sin_Skull_002.png");
	Skull->GetImageRenderer("LSkull_Top")->SetTransform({ { -SkullPos.X, 0.0f },  SkullScale });

	Skull->CreateImageRenderer("RSkull_Top", SinRenderOrder::Top);
	Skull->GetImageRenderer("RSkull_Top")->SetImage("Sin_Skull_002.png");
	Skull->GetImageRenderer("RSkull_Top")->SetTransform({ { SkullPos.X, 0.0f },  SkullScale });

	FVector ArmScale = { WinScale.X * 0.206f, WinScale.Y * 0.17f };
	FVector ArmPos = { WinScale.X * 0.306f, WinScale.Y * 0.04f };

	Skull->CreateImageRenderer("LArm", SinRenderOrder::Bottom);
	Skull->GetImageRenderer("LArm")->SetImage("Sin_LArm.png");
	Skull->GetImageRenderer("LArm")->SetTransform({ { -ArmPos.X, ArmPos.Y },  ArmScale });

	Skull->CreateImageRenderer("RArm", SinRenderOrder::Bottom);
	Skull->GetImageRenderer("RArm")->SetImage("Sin_RArm.png");
	Skull->GetImageRenderer("RArm")->SetTransform({ { ArmPos.X, ArmPos.Y },  ArmScale });

	AllMapRenderActors.push_back(Skull);
}

void SinChapterManager::M_CreateSinChain()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * SinChainSCale;
	FVector Pos = { WinScale.X * 0.412f, WinScale.Y * 0.12f };

	SinChain.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		SinChain.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid)));
		SinChain[i]->SetActorLocation({WinScale.hX(), Pos.Y});

		SinChain[i]->CreateImageRenderer("Left", SinRenderOrder::Mid);
		SinChain[i]->GetImageRenderer("Left")->SetImage("Sin_LChainLink.png");
		SinChain[i]->GetImageRenderer("Left")->SetTransform({ { -Pos.X, 0.0f }, Scale });

		SinChain[i]->CreateImageRenderer("Right", SinRenderOrder::Mid);
		SinChain[i]->GetImageRenderer("Right")->SetImage("Sin_RChainLink.png");
		SinChain[i]->GetImageRenderer("Right")->SetTransform({ { Pos.X, 0.0f }, Scale });

		Pos.Y += Scale.Y;

		AllMapRenderActors.push_back(SinChain[i]);
	}
}

void SinChapterManager::M_CreateSinPiston()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.125f, WinScale.Y * 0.740f };
	FVector UpPos = { WinScale.X * 0.41f, WinScale.Y * (-0.056f) };

	UpPiston = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Top));
	UpPiston->SetActorLocation({ WinScale.hX(), UpPos.Y });

	UpPiston->CreateImageRenderer("Left_Bottom", SinRenderOrder::Bottom);
	UpPiston->GetImageRenderer("Left_Bottom")->SetImage("Sin_BPiston.png");
	UpPiston->GetImageRenderer("Left_Bottom")->SetTransform({ { -UpPos.X, 0.0f }, Scale });
	
	UpPiston->CreateImageRenderer("Left_Top", SinRenderOrder::Top);
	UpPiston->GetImageRenderer("Left_Top")->SetImage("Sin_TPiston.png");
	UpPiston->GetImageRenderer("Left_Top")->SetTransform({ { -UpPos.X, 0.0f }, Scale });

	UpPiston->CreateImageRenderer("Right_Bottom", SinRenderOrder::Bottom);
	UpPiston->GetImageRenderer("Right_Bottom")->SetImage("Sin_BPiston.png");
	UpPiston->GetImageRenderer("Right_Bottom")->SetTransform({ { UpPos.X, 0.0f }, Scale });

	UpPiston->CreateImageRenderer("Right_Top", SinRenderOrder::Top);
	UpPiston->GetImageRenderer("Right_Top")->SetImage("Sin_TPiston.png");
	UpPiston->GetImageRenderer("Right_Top")->SetTransform({ { UpPos.X, 0.0f }, Scale });

	AllMapRenderActors.push_back(UpPiston);

	FVector DownPos = { WinScale.X * 0.41f, WinScale.Y * 1.24f };
	DownPiston = SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Bottom));
	DownPiston->SetActorLocation({ WinScale.hX(), DownPos.Y });

	DownPiston->CreateImageRenderer("Left", SinRenderOrder::Mid);
	DownPiston->GetImageRenderer("Left")->SetImage("Sin_TPiston.png");
	DownPiston->GetImageRenderer("Left")->SetTransform({ { -DownPos.X, 0.0f }, Scale });

	DownPiston->CreateImageRenderer("Right", SinRenderOrder::Mid);
	DownPiston->GetImageRenderer("Right")->SetImage("Sin_TPiston.png");
	DownPiston->GetImageRenderer("Right")->SetTransform({ { DownPos.X, 0.0f }, Scale });

	AllMapRenderActors.push_back(DownPiston);
}

void SinChapterManager::M_CreateSinBridge()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * SinBridgeScale;
	FVector Pos = { WinScale.hX(), WinScale.Y * 0.038f };

	SinBridge.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		SinBridge.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid)));
		SinBridge[i]->SetActorLocation(Pos);
		SinBridge[i]->CreateImageRenderer("Bridge", SinRenderOrder::Mid);
		SinBridge[i]->GetImageRenderer("Bridge")->SetImage("Sin_Bridge.png");
		SinBridge[i]->GetImageRenderer("Bridge")->SetTransform({ { 0.0f, 0.0f },  Scale });

		Pos.Y += Scale.Y;
		AllMapRenderActors.push_back(SinBridge[i]);
	}
}

void SinChapterManager::M_CreateThorn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;
	FVector Pos = { WinScale.X * 0.345f, WinScale.Y * 0.3f };

	UpThorn.resize(2);
	for (int y = 0; y < 2; y++)
	{
		float IntervalX = 0.0f;
		UpThorn[y].reserve(7);
		for (int x = 0; x < 7; x++)
		{
			UpThorn[y].push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid)));
			UpThorn[y][x]->SetActorLocation({ Pos.X + IntervalX, Pos.Y });
			UpThorn[y][x]->CreateImageRenderer("Thorn", SinRenderOrder::Mid);
			UpThorn[y][x]->GetImageRenderer("Thorn")->SetImage("Thorn_Idle.png");
			UpThorn[y][x]->GetImageRenderer("Thorn")->SetTransform({ {0, 0}, Scale });
			IntervalX += Scale.X * 1.08f;

			AllMapRenderActors.push_back(UpThorn[y][x]);
		}

		Pos.Y += Scale.Y;
	}


}

void SinChapterManager::Phase1(float _DeltaTime)
{
	SinPitMoveUpdate(_DeltaTime);
	SinBridgeMoveUpdate(_DeltaTime);
	SinChainMoveUpdate(_DeltaTime);
}

void SinChapterManager::Phase1Start()
{
	SinPitMoveOn();
	SinBridgeMoveOn();
	SinChainMoveOn();
}

void SinChapterManager::SinPitMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	for (SinComponent* Pit : SinPit)
	{
		if (nullptr == Pit)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Pit->MoveOn();
		float ScaleY = WinScale.Y * SinPitScale.Y;
		Pit->SetEndPosY(-(ScaleY * 0.5f));
		Pit->SetResetPosY(ScaleY * (static_cast<float>(SinPit.size()) - 0.5f));
	}
}

void SinChapterManager::SinPitMoveUpdate(float _DeltaTime)
{
	for (SinComponent* Pit : SinPit)
	{
		if (nullptr == Pit)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Pit->MoveUp(SinPitSpeedY, _DeltaTime);
	}
}

void SinChapterManager::SinBridgeMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	for (SinComponent* Bridge : SinBridge)
	{
		if (nullptr == Bridge)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Bridge->MoveOn();

		float ScaleY = WinScale.Y * SinBridgeScale.Y;
		Bridge->SetEndPosY(-(ScaleY * 0.5f));
		Bridge->SetResetPosY(ScaleY * (static_cast<float>(SinBridge.size()) - 0.5f));
	}
}

void SinChapterManager::SinBridgeMoveUpdate(float _DeltaTime)
{
	for (SinComponent* Bridge : SinBridge)
	{
		if (nullptr == Bridge)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Bridge->MoveUp(SinBridgeSpeedY, _DeltaTime);
	}
}

void SinChapterManager::SinChainMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	for (SinComponent* Chain : SinChain)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Chain->MoveOn();

		float ScaleY = WinScale.Y * SinChainSCale.Y;
		Chain->SetEndPosY(-(ScaleY * 0.5f));
		Chain->SetResetPosY(ScaleY * (static_cast<float>(SinChain.size()) - 0.5f));
	}
}

void SinChapterManager::SinChainMoveUpdate(float _DeltaTime)
{
	for (SinComponent* Chain : SinChain)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Chain->MoveUp(SinChainSpeedY, _DeltaTime);
	}
}

void SinChapterManager::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void SinChapterManager::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}

void SinChapterManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SinChapterManager::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinState::Intro:
		break;
	case ESinState::Phase1:
		Phase1(_DeltaTime);
		break;
	case ESinState::Phase2:
		break;
	}
}

void SinChapterManager::M_StateChange(ESinState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinState::Intro:
			break;
		case ESinState::Phase1:
			Phase1Start();
			break;
		case ESinState::Phase2:
			break;
		}
	}

	State = _State;
}
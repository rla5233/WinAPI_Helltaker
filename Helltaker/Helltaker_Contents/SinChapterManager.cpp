#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinComponent.h"
#include "Sin_Thorn.h"
#include "HeroLife.h"
#include "Shield.h"
#include "Bridge.h"
#include "Gear.h"
#include "Pit.h"

bool SinChapterManager::IsLoad = false;

const FVector SinChapterManager::SinChainSCale = { 0.0375f, 0.1388f };
const float SinChapterManager::SinChainSpeedY = -150.0f;

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

		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Skull_001.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Skull_002.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LArm.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RArm.png");
		
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_BPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_TPiston.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LChainLink.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RChainLink.png");

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinMap()
{
	M_CreateSinBG("SinBG");
	M_CreateSinPit();
	M_CreateSinGear();
	M_CreateSinShield();

	//
	M_CreateSinBridge();
	M_CreateSinSkull();
	M_CreateSinChain();
	M_CreateSinPiston();
	//
	
	M_CreateThorn();

	M_CreateSinHeroLife();
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
	float ScaleY = WinScale.Y * Pit::GetScale().Y;
	float PosY = WinScale.Y * 0.304f;

	SinPit.reserve(3);
	for (int i = 0; i < 3; i++)
	{		
		SinPit.push_back(SpawnActor<Pit>(static_cast<int>(SinUpdateOrder::UnderBackGround)));
		SinPit[i]->SetActorLocation({WinScale.hX(), PosY });
		SinPit[i]->StateChange(ESinPitState::Idle);
		PosY += ScaleY;
		
		AllMapRenderActors.push_back(SinPit[i]);
	}
}

void SinChapterManager::M_CreateSinGear()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.861f;
	SinGear = SpawnActor<Gear>(static_cast<int>(SinUpdateOrder::Bottom));
	SinGear->SetActorLocation({ WinScale.hX(), PosY });
	SinGear->StateChange(ESinGearState::Idle);
	
	AllMapRenderActors.push_back(SinGear);
}


void SinChapterManager::M_CreateSinHeroLife()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.962f;
	SinHeroLife = SpawnActor<HeroLife>(static_cast<int>(SinUpdateOrder::Top));
	SinHeroLife->SetActorLocation({ WinScale.hX(), PosY });
	SinHeroLife->StateChange(ESinHeroLifeState::Idle);

	AllMapRenderActors.push_back(SinHeroLife);
}

void SinChapterManager::M_CreateSinShield()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.322f;

	Shield* SinShield = SpawnActor<Shield>(static_cast<int>(SinUpdateOrder::Mid));
	SinShield->SetActorLocation({ WinScale.hX(), PosY });
	
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
	FVector Pos = { WinScale.hX(), WinScale.Y * 0.038f };
	float ScaleY = WinScale.Y * Bridge::GetScale().Y;

	SinBridge.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		SinBridge.push_back(SpawnActor<SinComponent>(static_cast<int>(SinUpdateOrder::Mid)));
		SinBridge[i]->SetActorLocation(Pos);

		Pos.Y += ScaleY;
		AllMapRenderActors.push_back(SinBridge[i]);
	}
}

void SinChapterManager::M_CreateThorn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * Sin_Thorn::GetThornScale();
	FVector UpPos = { WinScale.X * 0.345f, WinScale.Y * 0.23f };

	UpThorn.resize(3);
	for (int y = 0; y < 3; y++)
	{
		float IntervalX = 0.0f;
		UpThorn[y].reserve(7);

		for (int x = 0; x < 7; x++)
		{
			UpThorn[y].push_back(SpawnActor<Sin_Thorn>(static_cast<int>(SinUpdateOrder::Mid)));
			UpThorn[y][x]->SetActorLocation({ UpPos.X + IntervalX, UpPos.Y });

			if (y == 2)
			{
				UpThorn[y][x]->SetState(EThornState::Up);
			}
			else
			{
				UpThorn[y][x]->StateChange(EThornState::Idle);
			}

			IntervalX += Scale.X * 1.08f;

			AllMapRenderActors.push_back(UpThorn[y][x]);
		}

		UpPos.Y += Scale.Y * 1.1f;
	}

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.782f };

	DownThorn.resize(3);
	for (int y = 0; y < 3; y++)
	{
		float IntervalX = 0.0f;
		DownThorn[y].reserve(7);
		
		for (int x = 0; x < 7; x++)
		{
			DownThorn[y].push_back(SpawnActor<Sin_Thorn>(static_cast<int>(SinUpdateOrder::Mid)));
			DownThorn[y][x]->SetActorLocation({ DownPos.X + IntervalX, DownPos.Y });

			if (y == 0)
			{
				DownThorn[y][x]->StateChange(EThornState::Idle);
				DownThorn[y][x]->AllRenderersActiveOff(); 
			}
			else
			{
				DownThorn[y][x]->StateChange(EThornState::Idle);
			}
			
			IntervalX += Scale.X * 1.08f;

			AllMapRenderActors.push_back(DownThorn[y][x]);
		}

		DownPos.Y += Scale.Y * 1.1f;
	}
}

void SinChapterManager::IntroStart()
{
}

void SinChapterManager::Intro(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE))
	{
		M_StateChange(ESinState::Phase1);
	}
}


void SinChapterManager::Phase1Start()
{
	SinBridgeMoveOn();
	SinChainMoveOn();

	SinPitMoveOn();
	AllThornMoveOn();
	SinGear->StateChange(ESinGearState::Working);
}

void SinChapterManager::Phase1(float _DeltaTime)
{
	SinBridgeMoveUpdate(_DeltaTime);
	SinChainMoveUpdate(_DeltaTime);
}

void SinChapterManager::SinPitMoveOn()
{
	for (Pit* Pit : SinPit)
	{
		if (nullptr == Pit)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Pit->StateChange(ESinPitState::Move);
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

		Bridge->MoveY_Update(SinBridgeSpeedY, _DeltaTime);
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

		Chain->MoveY_Update(SinChainSpeedY, _DeltaTime);
	}
}

void SinChapterManager::AllThornMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * Sin_Thorn::GetThornScale();
	FVector UpPos = { WinScale.X * 0.345f, WinScale.Y * 0.23f };

	for (std::vector<Sin_Thorn*>& ThornVec : UpThorn)
	{
		for (Sin_Thorn* Thorn : ThornVec)
		{
			if (nullptr == Thorn)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Thorn->SetEndPosY(UpPos.Y - Scale.Y * 1.1f);
			Thorn->SetDownPosY(UpPos.Y);
			Thorn->SetUpPosY(UpPos.Y + Scale.Y * 1.5f);
			Thorn->SetResetPosY(UpPos.Y + 2.0f * Scale.Y * 1.1f);
			Thorn->MoveOn();
		}
	}

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.782f };

	for (std::vector<Sin_Thorn*>& ThornVec : DownThorn)
	{
		for (Sin_Thorn* Thorn : ThornVec)
		{
			if (nullptr == Thorn)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Thorn->SetEndPosY(DownPos.Y - Scale.Y * 1.1f);
			Thorn->SetDownPosY(DownPos.Y + Scale.Y * 0.6f);
			Thorn->SetUpPosY(DownPos.Y + 2.0f * Scale.Y * 1.1f);
			Thorn->SetResetPosY(DownPos.Y + 2.0f * Scale.Y * 1.1f);
			Thorn->MoveOn();
		}
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
		Intro(_DeltaTime);
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
			IntroStart();
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
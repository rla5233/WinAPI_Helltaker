#include "SinChapterManager.h"

#include "BackGround.h"
#include "SinMoveActor.h"
#include "ChainLink.h"
#include "Sin_Thorn.h"
#include "Sin_Hero.h"
#include "HeroLife.h"
#include "Shield.h"
#include "Bridge.h"
#include "Piston.h"
#include "Skull.h"
#include "Chain.h"
#include "Gear.h"
#include "Pit.h"

#include <EngineCore/EngineDebug.h>

bool SinChapterManager::IsLoad = false;

const float SinChapterManager::HeroDelayTime = 0.129f;

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

		IsLoad = true;
	}
}

void SinChapterManager::M_CreateSinMap()
{
	M_CreateSinBG("SinBG");
	M_CreateSinPit();
	M_CreateSinGear();

	M_CreateSinShield();

	M_CreateSinPiston();
	M_CreateSinSkull();
	M_CreateSinChainLink();

	M_CreateSinBridge();
	M_CreateThorn();
	
	M_CreateSinHeroLife();

	M_SpawnHero();

	FVector WinScale = ContentsHelper::GetWindowScale();
	Chain* NewChain = SpawnActor<Chain>(static_cast<int>(SinUpdateOrder::Top));
	NewChain->SetActorLocation({ WinScale.hX(), WinScale.hY() });
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
		SinPit[i]->SetName("SinPit");
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
	SinGear->SetName("SinGear");
	SinGear->SetActorLocation({ WinScale.hX(), PosY });
	SinGear->StateChange(ESinGearState::Idle);
	
	AllMapRenderActors.push_back(SinGear);
}


void SinChapterManager::M_CreateSinHeroLife()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.962f;
	SinHeroLife = SpawnActor<HeroLife>(static_cast<int>(SinUpdateOrder::Top));
	SinHeroLife->SetName("SinHeroLife");
	SinHeroLife->SetActorLocation({ WinScale.hX(), PosY });
	SinHeroLife->StateChange(ESinHeroLifeState::Idle);

	AllMapRenderActors.push_back(SinHeroLife);
}

void SinChapterManager::M_CreateSinShield()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.322f;

	Shield* SinShield = SpawnActor<Shield>(static_cast<int>(SinUpdateOrder::Mid));
	SinShield->SetName("SinShield");
	SinShield->SetActorLocation({ WinScale.hX(), PosY });
	
	AllMapRenderActors.push_back(SinShield);
}

void SinChapterManager::M_CreateSinSkull()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.665f;

	SinSkull = SpawnActor<Skull>(static_cast<int>(SinUpdateOrder::Top));
	SinSkull->SetName("SinSkull");
	SinSkull->SetActorLocation({ WinScale.hX(), PosY });
	SinSkull->StateChange(ESinSkullState::Idle);

	AllMapRenderActors.push_back(SinSkull);
}

void SinChapterManager::M_CreateSinChainLink()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * ChainLink::GetScale().Y;
	float PosY = WinScale.Y * 0.12f;

	SinChain.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		SinChain.push_back(SpawnActor<ChainLink>(static_cast<int>(SinUpdateOrder::Mid)));
		SinChain[i]->SetName("SinChain");
		SinChain[i]->SetActorLocation({ WinScale.hX(), PosY });
		SinChain[i]->StateChange(ESinChainState::Idle);

		PosY += ScaleY;

		AllMapRenderActors.push_back(SinChain[i]);
	}
}

void SinChapterManager::M_CreateSinPiston()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float UpPosY = WinScale.Y * (-0.056f);

	UpPiston = SpawnActor<Piston>(static_cast<int>(SinUpdateOrder::Top));
	UpPiston->SetName("SinPiston");
	UpPiston->SetActorLocation({ WinScale.hX(), UpPosY });
	UpPiston->StateChange(ESinPistonState::Idle);
	
	AllMapRenderActors.push_back(UpPiston);

	float DownPosY = WinScale.Y * 1.24f;
	DownPiston = SpawnActor<Piston>(static_cast<int>(SinUpdateOrder::Bottom));
	DownPiston->SetName("SinPiston");
	DownPiston->SetActorLocation({ WinScale.hX(), DownPosY });
	DownPiston->StateChange(ESinPistonState::Idle);

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
		SinBridge.push_back(SpawnActor<Bridge>(static_cast<int>(SinUpdateOrder::Mid)));
		SinBridge[i]->SetName("SinBridge");
		SinBridge[i]->SetActorLocation(Pos);
		SinBridge[i]->StateChange(ESinBridgeState::Idle);

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
			UpThorn[y][x]->SetName("UpThorn");
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
			DownThorn[y][x]->SetName("DownThorn");
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

void SinChapterManager::M_SpawnHero()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { WinScale.hX(), WinScale.Y * 0.576f };
	PlayerHero = SpawnActor<Sin_Hero>(static_cast<int>(SinUpdateOrder::Hero));
	PlayerHero->SetName("Sin_Hero");
	PlayerHero->SetActorLocation(Pos);
	PlayerHero->StateChange(EHeroState::Idle);

	AllMapRenderActors.push_back(PlayerHero);
}

void SinChapterManager::IntroStart()
{
	UpPiston->StateChange(ESinPistonState::Move);
}

void SinChapterManager::Intro(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);

	if (ESinSkullState::Idle == SinSkull->GetState() &&
		ESinPistonState::Idle == UpPiston->GetState())
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
	
	PlayerHero->SinHero_StateChange(ESinHeroState::MoveY);
	SinGear->StateChange(ESinGearState::Working);
}

void SinChapterManager::Phase1(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);
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
	for (Bridge* Bridge : SinBridge)
	{
		if (nullptr == Bridge)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Bridge->StateChange(ESinBridgeState::Move);
	}
}

void SinChapterManager::SinChainMoveOn()
{
	for (ChainLink* Chain : SinChain)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Chain->StateChange(ESinChainState::Move);
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

void SinChapterManager::HeroDelayTimeUpdate(float _DeltaTime)
{
	if (false == PlayerHero->GetCanActionCheck())
	{
		if (0.0f >= HeroDelayTimeCount)
		{
			PlayerHero->SetCanActionCheck(true);
			HeroDelayTimeCount = HeroDelayTime;
			return;
		}

		HeroDelayTimeCount -= _DeltaTime;
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
	DebugMode();
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

void SinChapterManager::DebugMode()
{
	if (UEngineInput::IsDown('B'))
	{
		GEngine->EngineDebugSwitch();
	}

	if (GEngine->IsDebug())
	{
		FVector CurPos = PlayerHero->GetActorLocation();

		UEngineDebug::DebugTextPrint("PlayerPos : " + CurPos.ToString(), 20);
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
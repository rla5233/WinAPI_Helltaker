#include "SinChapterManager.h"

#include "SinMoveActor.h"
#include "BackGround.h"
#include "SmallChain.h"
#include "ChainLink.h"
#include "Sin_Thorn.h"
#include "Sin_Hero.h"
#include "HeroLife.h"
#include "HitChain.h"
#include "Shield.h"
#include "Bridge.h"
#include "Piston.h"
#include "Skull.h"
#include "Gear.h"
#include "Pit.h"

#include <EngineCore/EngineDebug.h>

bool SinChapterManager::IsLoad = false;

const float SinChapterManager::HeroDelayTime = 0.13f;

const FVector SinChapterManager::SmallChainStartPos = { 0.345f, 0.48f };

const float SinChapterManager::Phase1_DelayTime = 0.5f;

const float SinChapterManager::StartPosY = 0.388f;
const float SinChapterManager::MaxSpeedY = -180.0f;

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
		ContentsHelper::LoadImg("UI", "White_Bar.png");

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
	M_SpawnHero();
	
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

	SinChain.reserve(2);
	for (int i = 0; i < 2; i++)
	{
		SinChain.push_back(SpawnActor<ChainLink>(static_cast<int>(SinUpdateOrder::Mid)));
		SinChain[i]->SetName("SinChain");
		SinChain[i]->SetActorLocation({ WinScale.hX(), PosY });
		SinChain[i]->StateChange(ESinChainLinkState::Idle);

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
	FVector UpPos = { WinScale.X * 0.345f, WinScale.Y * 0.222f };

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

		UpPos.Y += Scale.Y * 1.088f;
	}

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.784f };

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

		DownPos.Y += Scale.Y * 1.088f;
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

void SinChapterManager::M_CreateSmallChain(ESinSmallChainType _Type, int _PhaseNum, int _PosIndex, int _VecIndex)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector StartPos = WinScale * SmallChainStartPos;
	float TileScaleX = ContentsHelper::GetTileScale().X;
	float TileScaleY = WinScale.Y * Sin_Thorn::GetThornScale().Y * 1.088f;

	SmallChain* NewSmallChain = SpawnActor<SmallChain>(static_cast<int>(SinUpdateOrder::Mid));
	
	switch (_Type)
	{
	case ESinSmallChainType::Ver:
		NewSmallChain->SetActorLocation({ StartPos.X + TileScaleX * _PosIndex , WinScale.hY() });
		break;
	case ESinSmallChainType::Hor:
		NewSmallChain->SetActorLocation({ WinScale.hX(), StartPos.Y + TileScaleY * _PosIndex });
		break;
	}

	NewSmallChain->SetName("SmallChain");
	NewSmallChain->CreateImageRenderer(_Type);
	NewSmallChain->StateChange(ESinSmallChainState::Idle);

	switch (_PhaseNum)
	{
	case 1:
		Phase1_SmallChain[_VecIndex].push_back(NewSmallChain);
		break;
	case 2:
		Phase2_SmallChain[_VecIndex].push_back(NewSmallChain);
		break;
	}
}

void SinChapterManager::M_SetSmallChainVecSize(int _Size, int _PhaseNum)
{
	switch (_PhaseNum)
	{
	case 1:
		Phase1_SmallChain.resize(_Size);
		break;
	case 2:
		Phase2_SmallChain.resize(_Size);
		break;
	}
}

void SinChapterManager::M_CreateHitChain(ESinHitChainType _Type, int _PointY)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = { WinScale.X * 0.333f, WinScale.Y * 0.008f };
	float ScaleY = WinScale.Y * 0.182f;
	HitChain* NewHitChain = SpawnActor<HitChain>(static_cast<int>(SinUpdateOrder::Top));
	SinTile LocationPoint = { 0, _PointY * 2 };

	switch (_Type)
	{
	case ESinHitChainType::Left:
		NewHitChain->SetActorLocation({ WinScale.hX() - Pos.X, Pos.Y + (ScaleY * _PointY)});
		LocationPoint.X = 0;
		break;
	case ESinHitChainType::Right:
		NewHitChain->SetActorLocation({ WinScale.hX() + Pos.X, Pos.Y + (ScaleY * _PointY) });
		LocationPoint.X = 6;
		break;
	}

	NewHitChain->SetCurPoint(LocationPoint);
	NewHitChain->SetName("HitChain");
	NewHitChain->SetType(_Type);

	NewHitChain->StateChange(ESinHitChainState::Idle);

	AllHitChain[LocationPoint.Key] = NewHitChain;
}

bool SinChapterManager::HitChainHitCheck(SinTile _Point)
{
	if (true == AllHitChain.contains(_Point.Key) )
	{
		if (true == AllHitChain[_Point.Key]->IsCanHit())
		{
			AllHitChain[_Point.Key]->StateChange(ESinHitChainState::None);
			AllHitChain[_Point.Key]->StateChange(ESinHitChainState::Hit);
			return true;
		}
	}

	return false;
}

void SinChapterManager::HitChainDeathUpdate(SinTile _Point)
{
	if (false == AllHitChain.contains(_Point.Key))
	{
		MsgBoxAssert("Fatal Error");
	}

	AllHitChain.erase(_Point.Key);
}

void SinChapterManager::IntroStart()
{
	UpPiston->StateChange(ESinPistonState::Move);
}

void SinChapterManager::Intro(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);

	if (ESinSkullState::Move == SinSkull->GetState() &&
		ESinPistonState::Move == UpPiston->GetState())
	{
		M_StateChange(ESinState::Phase1);
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		M_StateChange(ESinState::Phase1);
	}
}

void SinChapterManager::Phase1_Start()
{
	SinBridgeMoveOn();
	SinChainMoveOn();
	
	SinPitMoveOn();
	AllThornMoveOn();
	
	PlayerHero->SinHero_StateChange(ESinHeroState::MoveY);
	SinGear->StateChange(ESinGearState::Working);

	MoveYSum = 0;
	PhaseSmallChainVec_Index = 0;
	PhaseDelayTimeCount = Phase1_DelayTime;
	Phase1_Order = 0;
}

void SinChapterManager::Phase1(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);
	MoveYSum += SpeedY * _DeltaTime;
	Phase1_SmallChainUpdate(_DeltaTime);
	
	switch (Phase1_Order)
	{
	case 0:
		BridgeResetCheck();
		Phase1_SpeedY_Update1(_DeltaTime);
		break;
	case 1:
		Phase1_SpeedY_Update2(_DeltaTime);
		break;
	}
	
	// Debug
	if (UEngineInput::IsDown(VK_SPACE))
	{
		Phase1_SmallChain.clear();
		M_StateChange(ESinState::Phase2);
	}
}

void SinChapterManager::Phase1_SmallChainUpdate(float _DeltaTime)
{
	if (PhaseSmallChainVec_Index >= Phase1_SmallChain.size())
	{
		return;
	}

	if (0.0f >= PhaseDelayTimeCount)
	{
		std::list<SmallChain*>& SmallChainVec = Phase1_SmallChain[PhaseSmallChainVec_Index];

		for (SmallChain* SmallChain : SmallChainVec)
		{
			if (nullptr == SmallChain)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			SmallChain->StateChange(ESinSmallChainState::Show);
		}

		++PhaseSmallChainVec_Index;
		PhaseDelayTimeCount = Phase1_DelayTime;

		return;
	}

	PhaseDelayTimeCount -= _DeltaTime;
}

void SinChapterManager::Phase1_SpeedY_Update1(float _DeltaTime)
{
	if (MaxSpeedY < SpeedY)
	{
		SpeedY += -90.0f * _DeltaTime;

		if (MaxSpeedY >= SpeedY)
		{
			SpeedY = MaxSpeedY;
		}
	}
}

void SinChapterManager::Phase1_SpeedY_Update2(float _DeltaTime)
{
	if (0.0f > SpeedY)
	{
		SpeedY += AccY * _DeltaTime;

		FVector WinScale = ContentsHelper::GetWindowScale();
		float CurPosY = SinBridge[0]->GetActorLocation().Y;
		float TarGetPosY = WinScale.Y * (0.04f + Bridge::GetScale().Y);

		if (0.0f <= SpeedY)
		{
			SpeedY = 0.0f;
			M_StateChange(ESinState::Phase2);
		}
	}
}

void SinChapterManager::BridgeResetCheck()
{
	if (5 == BridgeResetCount)
	{
		FVector WinScale = ContentsHelper::GetWindowScale();

		float CurPosY = SinBridge[0]->GetActorLocation().Y;
		float TarGetPosY = WinScale.Y * (0.038f + Bridge::GetScale().Y);

		AccY = -(SpeedY * SpeedY) / (2 * (TarGetPosY - CurPosY));
		++Phase1_Order;
	}
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

		Chain->StateChange(ESinChainLinkState::Move);
	}
}

// 수정 (리팩토링 가능?)
void SinChapterManager::AllThornMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * Sin_Thorn::GetThornScale();
	FVector UpPos = { WinScale.X * 0.345f, WinScale.Y * 0.222f };

	for (std::vector<Sin_Thorn*>& ThornVec : UpThorn)
	{
		for (Sin_Thorn* Thorn : ThornVec)
		{
			if (nullptr == Thorn)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Thorn->SetEndPosY(UpPos.Y - Scale.Y * 1.088f);
			Thorn->SetDownPosY(UpPos.Y);
			Thorn->SetUpPosY(UpPos.Y + Scale.Y * 1.3f);
			Thorn->SetResetPosY(UpPos.Y + 2.0f * Scale.Y * 1.088f);
			Thorn->MoveOn();
		}
	}

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.784f };

	for (std::vector<Sin_Thorn*>& ThornVec : DownThorn)
	{
		for (Sin_Thorn* Thorn : ThornVec)
		{
			if (nullptr == Thorn)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Thorn->SetEndPosY(DownPos.Y - Scale.Y * 1.088f);
			Thorn->SetDownPosY(DownPos.Y + Scale.Y * 0.7f);
			Thorn->SetUpPosY(DownPos.Y + 2.0f * Scale.Y * 1.088f);
			Thorn->SetResetPosY(DownPos.Y + 2.0f * Scale.Y * 1.088f);
			Thorn->MoveOn();
		}
	}
}

void SinChapterManager::Phase2_Start()
{

}

void SinChapterManager::Phase2(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);
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
		Phase2(_DeltaTime);
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
		SinTile CurPoint= PlayerHero->GetCurPoint();
		std::string CPoint = "[ ";
		CPoint += std::to_string(CurPoint.X) + ", " + std::to_string(CurPoint.Y) + " ]";

		UEngineDebug::DebugTextPrint("PlayerPos : " + CurPos.ToString(), 20);
		UEngineDebug::DebugTextPrint("PlayerPoint : " + CPoint, 20);

		for (std::pair<const __int64, HitChain*>& Chain : AllHitChain)
		{
			SinTile point = Chain.second->GetCurPoint();
			int count = Chain.second->GetHitCount();

			std::string CPoint = "( ";
			CPoint += std::to_string(point.X) + ", " + std::to_string(point.Y) + " )";

			UEngineDebug::DebugTextPrint("HitChain : " + CPoint + ", " + std::to_string(count), 20);
		}
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
			Phase1_Start();
			break;
		case ESinState::Phase2:
			Phase2_Start();
			break;
		}
	}

	State = _State;
}
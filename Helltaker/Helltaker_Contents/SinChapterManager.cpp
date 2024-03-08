#include "SinChapterManager.h"

#include "SinMoveActor.h"
#include "BackGround.h"
#include "HitChainHp.h"
#include "SmallChain.h"
#include "ChainLink.h"
#include "Sin_Thorn.h"
#include "Sin_Demon.h"
#include "Sin_Hero.h"
#include "HeroLife.h"
#include "HitChain.h"
#include "Shield.h"
#include "Bridge.h"
#include "Piston.h"
#include "Skull.h"
#include "Scene.h"
#include "Gear.h"
#include "Pit.h"

#include <EngineCore/EngineDebug.h>
#include <EnginePlatform/EngineSound.h>

bool SinChapterManager::IsLoad = false;
std::set<std::string> SinChapterManager::ChapterSet;

const float SinChapterManager::TransitionInter = 0.0435f;
const float SinChapterManager::HeroDelayTime = 0.13f;

const FVector SinChapterManager::SmallChainStartPos = { 0.345f, 0.48f };

const float SinChapterManager::IntroDelayTime = 0.9f;
float SinChapterManager::Phase1_StartDelayTime = 2.6f;
const float SinChapterManager::CutSceneDelayTime = 0.5f;

float SinChapterManager::SmallChainDelayTime = 0.0f;

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

void SinChapterManager::CreateTransition()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	TransitionActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Transition));
	TransitionActor->SetName("Transition");
	TransitionActor->CreateImageRenderer(RenderOrder::Transition);
	TransitionActor->SetActorLocation(WinScale.Half2D());
	TransitionActor->GetImageRenderer()->SetTransform({ { 0, 0 }, WinScale });
	TransitionActor->GetImageRenderer()->SetImage("Transition");
	TransitionActor->GetImageRenderer()->CreateAnimation("Transition", "Transition", 0, 28, TransitionInter, false);
	TransitionActor->GetImageRenderer()->CameraEffectOff();
	TransitionActor->GetImageRenderer()->ActiveOff();
	
	AllMapRenderActors.push_back(TransitionActor);
}

void SinChapterManager::TransitionOn()
{
	TransitionActor->ActiveOn();
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->AnimationReset();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition");
	UEngineSound::SoundPlay("transition_on.wav");
}

void SinChapterManager::M_CreateSinMap(int _ChapterNum)
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
	
	M_CreateSinHeroLife(_ChapterNum);
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


void SinChapterManager::M_CreateSinHeroLife(int _ChapterNum)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.962f;
	SinHeroLife = SpawnActor<HeroLife>(static_cast<int>(SinUpdateOrder::Top));
	SinHeroLife->SetName("SinHeroLife");
	SinHeroLife->SetActorLocation({ WinScale.hX(), PosY });
	SinHeroLife->SetSinChapterNum(_ChapterNum);
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

	SinChainLink.reserve(2);
	for (int i = 0; i < 2; i++)
	{
		SinChainLink.push_back(SpawnActor<ChainLink>(static_cast<int>(SinUpdateOrder::Mid)));
		SinChainLink[i]->SetName("SinChain");
		SinChainLink[i]->SetActorLocation({ WinScale.hX(), PosY });
		SinChainLink[i]->StateChange(ESinChainLinkState::Idle);

		PosY += ScaleY;

		AllMapRenderActors.push_back(SinChainLink[i]);
	}
}

void SinChapterManager::M_CreateSinPiston()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float UpPosY = WinScale.Y * (-0.056f);

	UpPiston = SpawnActor<Piston>(static_cast<int>(SinUpdateOrder::Top));
	UpPiston->SetName("SinPiston");
	UpPiston->SetActorLocation({ WinScale.hX(), UpPosY });
	UpPiston->SetType(ESinPistonType::Up);
	UpPiston->StateChange(ESinPistonState::Idle);
	
	AllMapRenderActors.push_back(UpPiston);

	float DownPosY = WinScale.Y * 1.24f;
	DownPiston = SpawnActor<Piston>(static_cast<int>(SinUpdateOrder::Bottom));
	DownPiston->SetName("SinPiston");
	DownPiston->SetActorLocation({ WinScale.hX(), DownPosY });
	DownPiston->SetType(ESinPistonType::Down);
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

	UpThorn.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		UpThorn.push_back(SpawnActor<Sin_Thorn>(static_cast<int>(SinUpdateOrder::Mid)));
		UpThorn[i]->SetName("UpThorn");
		UpThorn[i]->SetActorLocation({ UpPos.X, UpPos.Y });

		if (i == 2)
		{
			UpThorn[i]->SetState(EThornState::Up);
		}
		else
		{
			UpThorn[i]->StateChange(EThornState::Idle);
		}

		UpPos.Y += Scale.Y * 1.088f;
		AllMapRenderActors.push_back(UpThorn[i]);
	}

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.784f };
	
	DownThorn.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		DownThorn.push_back(SpawnActor<Sin_Thorn>(static_cast<int>(SinUpdateOrder::Mid)));
		DownThorn[i]->SetName("DownThorn");
		DownThorn[i]->SetActorLocation({ DownPos.X, DownPos.Y });

		if (i == 0)
		{
			DownThorn[i]->SetState(EThornState::Idle);
			DownThorn[i]->AllRenderersActiveOff();
		}
		else
		{
			DownThorn[i]->StateChange(EThornState::Idle);
		}

		DownPos.Y += Scale.Y * 1.088f;
		AllMapRenderActors.push_back(DownThorn[i]);
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

void SinChapterManager::M_SpawnDemon()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.12f;
	Judge = SpawnActor<Sin_Demon>(static_cast<int>(SinUpdateOrder::Top));
	Judge->SetActorLocation({ WinScale.hX(), PosY });
	Judge->SetDemon("Judge", { { 0.0f, 0.0f }, WinScale * Sin_Demon::GetIdleScale() });
	Judge->StateChange(EDemonState::Sin_Appear);

	AllMapRenderActors.push_back(Judge);
}

void SinChapterManager::M_CreateSmallChain(
	ESinSmallChainType _Type,
	ESinPhase _Phase,
	int _PosIndex, 
	int _VecIndex)
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
		if (ESinPhase::Phase2 == _Phase)
		{
			NewSmallChain->SetActorLocation({ WinScale.hX(), StartPos.Y + TileScaleY * (_PosIndex - 1) });
		}
		else
		{
			NewSmallChain->SetActorLocation({ WinScale.hX(), StartPos.Y + TileScaleY * _PosIndex });
		}
		break;
	}

	NewSmallChain->SetPhase(_Phase);
	NewSmallChain->SetName("SmallChain");
	NewSmallChain->CreateImageRenderer(_Type);
	NewSmallChain->StateChange(ESinSmallChainState::Idle);

	switch (_Phase)
	{
	case ESinPhase::Phase1:
		NewSmallChain->SetPhase1_Idx(_VecIndex);
		Phase1_SmallChain[_VecIndex].push_back(NewSmallChain);
		break;
	case ESinPhase::Phase2:
		Phase2_SmallChain[_VecIndex].push_back(NewSmallChain);
		break;
	}
}

void SinChapterManager::M_CreateSmallVerChain_P1(int _PosIndex, int _VecIndex)
{
	M_CreateSmallChain(ESinSmallChainType::Ver, ESinPhase::Phase1, _PosIndex, _VecIndex);
}

void SinChapterManager::M_CreateSmallHorChain_P1(int _PosIndex, int _VecIndex)
{
	M_CreateSmallChain(ESinSmallChainType::Hor, ESinPhase::Phase1, _PosIndex, _VecIndex);
}

void SinChapterManager::M_CreateSmallVerChain_P2(int _PosIndex, int _VecIndex)
{
	M_CreateSmallChain(ESinSmallChainType::Ver, ESinPhase::Phase2, _PosIndex, _VecIndex);
}

void SinChapterManager::M_CreateSmallHorChain_P2(int _PosIndex, int _VecIndex)
{
	M_CreateSmallChain(ESinSmallChainType::Hor, ESinPhase::Phase2, _PosIndex, _VecIndex);
}

void SinChapterManager::M_SetSmallChainVecSize(int _Size, ESinPhase _Phase)
{
	switch (_Phase)
	{
	case ESinPhase::Phase1:
		Phase1_SmallChain.resize(_Size);
		break;
	case ESinPhase::Phase2:
		Phase2_SmallChain.resize(_Size);
		break;
	}
}

void SinChapterManager::M_SmallChainDeathCall(int _VecIndex)
{
	Phase1_SmallChain[_VecIndex].clear();
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

void SinChapterManager::M_CreateHitChainHp(std::string_view _Name /* = " " */)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * 0.125f;
	
	SinHitChainHp = SpawnActor<HitChainHp>(static_cast<int>(SinUpdateOrder::Top));
	SinHitChainHp->SetActorLocation({ WinScale.hX(), PosY });
	SinHitChainHp->GetTextRenderer()->SetText(_Name);
	SinHitChainHp->GetTextRenderer()->SetTextSize(40);
	SinHitChainHp->GetTextRenderer()->SetTextColor(Color8Bit::White);
	SinHitChainHp->GetTextRenderer()->SetFont("¸¼Àº °íµñ");
	SinHitChainHp->GetTextRenderer()->SetPosition({ 0.0f, WinScale.Y * (-0.06f) });
	SinHitChainHp->SetTotalHitCount(static_cast<int>(AllHitChain.size()));
	SinHitChainHp->StateChange(ESinHitChainHpState::Idle);

	AllMapRenderActors.push_back(SinHitChainHp);
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
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	PlayerHero->SeeDirChange(EActorSeeDir::Right);
	PlayerHero->StateChange(EHeroState::Idle);
	UEngineSound::SoundPlay("transition_off.wav");
	
	TimeCount = IntroDelayTime;
	OrderCount = 0;
}

void SinChapterManager::Intro(float _DeltaTime)
{
	HeroDelayTimeUpdate(_DeltaTime);

	switch (OrderCount)
	{
	case 0:
		TransitionCheck(_DeltaTime);
		break;
	case 1:
		Phase1_Check();
		break;
	}

	// Debug
	if (UEngineInput::IsDown(VK_SPACE))
	{
		M_StateChange(ESinState::Phase1);
	}
}

void SinChapterManager::TransitionCheck(float _DeltaTime)
{
	if (true == TransitionActor->GetImageRenderer()->IsCurAnimationEnd())
	{
		TransitionActor->GetImageRenderer()->ActiveOff();
		ResetCheck();

		if (0.0f > TimeCount)
		{
			UpPiston->StateChange(ESinPistonState::Move);
			++OrderCount;

			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void SinChapterManager::Phase1_Check()
{
	ResetCheck();
	if (ESinSkullState::Move == SinSkull->GetState() &&
		ESinPistonState::Move == UpPiston->GetState())
	{
		M_StateChange(ESinState::Phase1);
	}
}

void SinChapterManager::Phase1_Start()
{
	SinBridgeMoveOn();
	SinChainLinkMoveOn();
	
	SinPitMoveOn();
	AllThornMoveOn();
	
	PlayerHero->SinHero_StateChange(ESinHeroState::MoveY);
	SinGear->StateChange(ESinGearState::Working);

	SpeedY = 50.0f;
	MoveYSum = 0;
	BridgeResetCount = 0;

	SmallChainVec_Index = 0;
	SmallChainDelayTime = 0.6f;
	PhaseTimeCount = SmallChainDelayTime;

	TimeCount = Phase1_StartDelayTime;
	OrderCount = 0;
}

void SinChapterManager::Phase1(float _DeltaTime)
{
	ResetCheck();
	HeroDelayTimeUpdate(_DeltaTime);
	MoveYSum += SpeedY * _DeltaTime;
	
	Phase1_SmallChainUpdate(_DeltaTime);
	
	switch (OrderCount)
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
		M_StateChange(ESinState::Phase2);
	}
}

void SinChapterManager::Phase1_SmallChainUpdate(float _DeltaTime)
{
	if (0.0f < TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	if (SmallChainVec_Index >= Phase1_SmallChain.size())
	{
		return;
	}

	if (0.0f >= PhaseTimeCount)
	{
		std::list<SmallChain*>& SmallChainVec = Phase1_SmallChain[SmallChainVec_Index];

		for (SmallChain* SmallChain : SmallChainVec)
		{
			if (nullptr == SmallChain)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			SmallChain->StateChange(ESinSmallChainState::Show);
		}

		++SmallChainVec_Index;
		PhaseTimeCount = SmallChainDelayTime;

		return;
	}

	PhaseTimeCount -= _DeltaTime;
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
		++OrderCount;
	}
}

void SinChapterManager::Phase2_Start()
{
	SinPitMoveOff();
	SinBridgeMoveOff();
	SinChainLinkMoveOff();
	AllThornMoveOff();

	DownPiston->StateChange(ESinPistonState::Move);
	SinGear->StateChange(ESinGearState::Stop);

	PlayerHero->MoveY_Off();
	PlayerHero->SinHero_StateChange(ESinHeroState::Idle);

	SmallChainVec_Index = 0;
	SmallChainDelayTime = 0.8f;
	PhaseTimeCount = SmallChainDelayTime;

	MoveYSum = 0.0f;
	OrderCount = 0;
}

void SinChapterManager::ResetCheck()
{
	if (UEngineInput::IsPress('R'))
	{
		M_StateChange(ESinState::Reset);
	}
}

void SinChapterManager::Phase2(float _DeltaTime)
{
	ResetCheck();
	HeroDelayTimeUpdate(_DeltaTime);
	
	switch (OrderCount)
	{
	case 0:
		Phase2_SmallChainUpdate(_DeltaTime);
		HitChainCheck();
		break;
	case 1:
		JudgeAppear(_DeltaTime);
		break;
	}
}

void SinChapterManager::Phase2_SmallChainUpdate(float _DeltaTime)
{
	if (true == Phase2_SmallChain.empty())
	{
		return;
	}

	if (0.0f >= PhaseTimeCount)
	{
		std::list<SmallChain*>& SmallChainVec = Phase2_SmallChain[SmallChainVec_Index];

		for (SmallChain* SmallChain : SmallChainVec)
		{
			if (nullptr == SmallChain)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			SmallChain->StateChange(ESinSmallChainState::Show);
		}

		++SmallChainVec_Index;

		if (static_cast<int>(Phase2_SmallChain.size()) <= SmallChainVec_Index)
		{
			SmallChainVec_Index = 0;
		}

		PhaseTimeCount = SmallChainDelayTime;

		return;
	}

	PhaseTimeCount -= _DeltaTime;
}

void SinChapterManager::HitChainCheck()
{
	if (true == AllHitChain.empty())
	{
		M_SpawnDemon();
		TimeCount = CutSceneDelayTime;
		++OrderCount;
	}
}

void SinChapterManager::JudgeAppear(float _DeltaTime)
{
	if (true == Judge->GetImageRenderer()->IsCurAnimationEnd())
	{
		if (0.0f > TimeCount)
		{
			M_StateChange(ESinState::CutScene);
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void SinChapterManager::HeroDeathStart()
{
	for (AActor* Actor : AllMapRenderActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->AllRenderersActiveOff();
		Actor->ActiveOff();
	}

	for (size_t i = 0; i < Phase1_SmallChain.size(); i++)
	{
		for (AActor* Actor : Phase1_SmallChain[i])
		{
			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Actor->AllRenderersActiveOff();
			Actor->ActiveOff();
		}
	}

	for (size_t i = 0; i < Phase2_SmallChain.size(); i++)
	{
		for (AActor* Actor : Phase2_SmallChain[i])
		{
			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Actor->AllRenderersActiveOff();
			Actor->ActiveOff();
		}
	}

	for (std::pair<const __int64, HitChain*>& Actor : AllHitChain)
	{
		if (nullptr == Actor.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor.second->AllRenderersActiveOff();
		Actor.second->ActiveOff();
	}

	PlayerHero->ActiveOn();
	PlayerHero->GetImageRenderer()->ActiveOn();
}

void SinChapterManager::HeroDeath(float _DeltaTime)
{
	if (true == PlayerHero->GetImageRenderer()->IsCurAnimationEnd())
	{
		M_StateChange(ESinState::Reset);
	}
}

void SinChapterManager::CutSceneStart()
{
	for (AActor* Actor : AllMapRenderActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr.");
		}

		Actor->AllRenderersActiveOff();
		Actor->ActiveOff();
	}

	for (size_t i = 0; i < Phase2_SmallChain.size(); i++)
	{
		for (SmallChain* Actor : Phase2_SmallChain[i])
		{
			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor is nullptr.");
			}

			Actor->AllRenderersActiveOff();
			Actor->ActiveOff();
		}
	}
}

void SinChapterManager::CutScene(float _DeltaTime)
{
	ResetCheck();
}

void SinChapterManager::ResetStart()
{
	TransitionOn();
}

void SinChapterManager::Reset(float _DeltaTime)
{
	if (19 == TransitionActor->GetImageRenderer()->GetCurAnimationFrame())
	{
		LevelEnd(nullptr);
		LevelStart(nullptr);
	}
}

void SinChapterManager::SinChageStart()
{
	TransitionOn();
}

void SinChapterManager::SinChage(float _DeltaTime)
{
	if (19 == TransitionActor->GetImageRenderer()->GetCurAnimationFrame())
	{
		ChangeChapter();
	}
}

void SinChapterManager::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	CreateTransition();
}

void SinChapterManager::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	UpThorn.clear();
	DownThorn.clear();
	SinPit.clear();
	SinChainLink.clear();
	SinBridge.clear();

	for (AActor* Actor : AllMapRenderActors)
	{
		if (nullptr == Actor)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor->Destroy();
		Actor = nullptr;
	}

	for (std::pair<const __int64, HitChain*> Actor : AllHitChain)
	{
		if (nullptr == Actor.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor.second->Destroy();
		Actor.second = nullptr;
	}

	for (std::list<SmallChain*>& SmallChainList : Phase1_SmallChain)
	{
		for (SmallChain* Actor : SmallChainList)
		{
			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Actor->Destroy();
			Actor = nullptr;
		}
	}

	for (std::list<SmallChain*>& SmallChainList : Phase2_SmallChain)
	{
		for (SmallChain* Actor : SmallChainList)
		{
			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor is nullptr");
			}

			Actor->Destroy();
			Actor = nullptr;
		}
	}


	AllMapRenderActors.clear();
	AllHitChain.clear();

	for (size_t i = 0; i < Phase1_SmallChain.size(); i++)
	{
		Phase1_SmallChain[i].clear();
	}
	Phase1_SmallChain.clear();

	for (size_t i = 0; i < Phase2_SmallChain.size(); i++)
	{
		Phase2_SmallChain[i].clear();
	}
	Phase2_SmallChain.clear();
}

void SinChapterManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
	DebugMode();
	// Debug
	if (UEngineInput::IsPress('P'))
	{
		M_StateChange(ESinState::CutScene);
	}
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
	case ESinState::CutScene:
		CutScene(_DeltaTime);
		break;
	case ESinState::HeroDeath:
		HeroDeath(_DeltaTime);
		break;
	case ESinState::Reset:
		Reset(_DeltaTime);
		break;
	case ESinState::SinChage:
		SinChage(_DeltaTime);
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
			Phase1_Start();
			break;
		case ESinState::Phase2:
			Phase2_Start();
			break;
		case ESinState::CutScene:
			CutSceneStart();
			break;
		case ESinState::HeroDeath:
			HeroDeathStart();
			break;
		case ESinState::Reset:
			ResetStart();
			break;
		case ESinState::SinChage:
			SinChageStart();
			break;
		}
	}

	State = _State;
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

void SinChapterManager::SinChainLinkMoveOn()
{
	for (ChainLink* Chain : SinChainLink)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Chain->StateChange(ESinChainLinkState::Move);
	}
}

// ¼öÁ¤ (¸®ÆÑÅä¸µ °¡´É?)
void SinChapterManager::AllThornMoveOn()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * Sin_Thorn::GetThornScale();
	FVector UpPos = { WinScale.X * 0.345f, WinScale.Y * 0.222f };

	for (Sin_Thorn* Thorn : UpThorn)
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

	FVector DownPos = { WinScale.X * 0.345f, WinScale.Y * 0.784f };

	for (Sin_Thorn* Thorn : DownThorn)
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

void SinChapterManager::SinPitMoveOff()
{
	for (Pit* _Pit : SinPit)
	{
		if (nullptr == _Pit)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		_Pit->StateChange(ESinPitState::Idle);
	}
}

void SinChapterManager::SinBridgeMoveOff()
{
	for (Bridge* _Bridge : SinBridge)
	{
		if (nullptr == _Bridge)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		_Bridge->StateChange(ESinBridgeState::Idle);
	}
}

void SinChapterManager::SinChainLinkMoveOff()
{
	for (ChainLink* _ChainLink : SinChainLink)
	{
		if (nullptr == _ChainLink)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		_ChainLink->StateChange(ESinChainLinkState::Idle);
	}
}

void SinChapterManager::AllThornMoveOff()
{
	for (Sin_Thorn* Thorn : UpThorn)
	{
		if (nullptr == Thorn)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Thorn->MoveOff();
	}

	for (Sin_Thorn* Thorn : DownThorn)
	{
		if (nullptr == Thorn)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Thorn->MoveOff();
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
		SinTile CurPoint = PlayerHero->GetCurPoint();
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
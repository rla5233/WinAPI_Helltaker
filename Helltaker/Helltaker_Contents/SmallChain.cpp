#include "SmallChain.h"

#include "SinChapterManager.h"
#include "Sin_Thorn.h"	
#include "Sin_Hero.h"

#include <EngineBase/EngineRandom.h>

bool SmallChain::IsLoad = false;
bool SmallChain::IsHitSound = false;

const FVector SmallChain::V_Scale = { 0.03f, 1.0f };
const FVector SmallChain::H_Scale = { 1.0f, 0.052f };
const float SmallChain::HitStartDelay = 0.06f;
const float SmallChain::HitTime = 0.125f;

SmallChain::SmallChain()
{
}

SmallChain::~SmallChain()
{
}

void SmallChain::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_VChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_HChain.png");

		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_blink_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_blink_002.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_blink_003.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_blink_004.wav");

		//UEngineSound::SoundPlay("Vitality.wav");

		IsLoad = true;
	}
}

void SmallChain::CreateImageRenderer(ESinSmallChainType _Type)
{
	switch (_Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::SmallVChain);
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
		break;
	}

	Type = _Type;
}

void SmallChain::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	switch (Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer->SetImage("Sin_VChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * V_Scale } });
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer->SetImage("Sin_HChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * H_Scale } });
		MoveOn();
		break;
	}

	ImageRenderer->SetAlpha(0.25);
	ImageRenderer->ActiveOff();
}

void SmallChain::Idle(float _DeltaTime)
{
}

void SmallChain::ShowStart()
{
	if (ESinSmallChainType::Hor == Type)
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		float ScaleY = WinScale.Y * Sin_Thorn::GetThornScale().Y * 1.088f;
		float a = GetSinChapter()->M_GetMoveYSum();
		AddActorLocation({ 0.0f, fmodf(GetSinChapter()->M_GetMoveYSum(), ScaleY) });
	}

	ImageRenderer->ActiveOn();
	IsHitSound = false;
	IsShow = true;
	TimeCount = 0.0f;
}

void SmallChain::Show(float _DeltaTime)
{
	ShowAnimation(_DeltaTime);
	MoveY_Update(_DeltaTime);

	if (false == IsShow)
	{
		if (0.0f > TimeCount)
		{
			StateChange(ESinSmallChainState::Hit);
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void SmallChain::ShowAnimation(float _DeltaTime)
{
	if (true == IsShow)
	{
		switch (Type)
		{
		case ESinSmallChainType::Ver:
			VerShowAnimation(_DeltaTime);
			break;
		case ESinSmallChainType::Hor:
			HorShowAnimation(_DeltaTime);
			break;
		}
	}
}

void SmallChain::VerShowAnimation(float _DeltaTime)
{
	if (true)
	{
		TimeCount += _DeltaTime * 2.5f;

		FVector WinScale = ContentsHelper::GetWindowScale();
		float ScaleX = ContentsHelper::LerpClampf(V_Scale.X, 0.0f, TimeCount);
		ImageRenderer->SetScale({ WinScale.X * ScaleX, WinScale.Y * V_Scale.Y });

		if (1.0f <= TimeCount)
		{
			TimeCount = HitStartDelay;
			IsShow = false;
		}
	}
}

void SmallChain::HorShowAnimation(float _DeltaTime)
{
	if (true)
	{
		TimeCount += _DeltaTime * 2.5f;

		FVector WinScale = ContentsHelper::GetWindowScale();
		float ScaleY = ContentsHelper::LerpClampf(H_Scale.Y, 0.0f, TimeCount);
		ImageRenderer->SetScale({ WinScale.X * H_Scale.X, WinScale.Y * ScaleY });

		if (1.0f <= TimeCount)
		{
			TimeCount = HitStartDelay;
			IsShow = false;
		}
	}
}

void SmallChain::HitStart()
{
	if (false == IsHitSound)
	{
		int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 4);
		switch (RandomValue)
		{
		case 1:
			UEngineSound::SoundPlay("boss_chain_blink_001.wav");
			break;
		case 2:
			UEngineSound::SoundPlay("boss_chain_blink_002.wav");
			break;
		case 3:
			UEngineSound::SoundPlay("boss_chain_blink_003.wav");
			break;
		case 4:
			UEngineSound::SoundPlay("boss_chain_blink_004.wav");
			break;
		}
		
		IsHitSound = true;
	}

	ImageRenderer->SetAlpha(1);
	IsHit = true;
	TimeCount = 0.0f;
	HitTimeCount = HitTime;
}

void SmallChain::Hit(float _DeltaTime)
{
	HitAnimation(_DeltaTime);
	MoveY_Update(_DeltaTime);
	HeroHitCheck(_DeltaTime);
}

void SmallChain::HitAnimation(float _DeltaTime)
{
	if (true == IsHit)
	{
		switch (Type)
		{
		case ESinSmallChainType::Ver:
			VerHitAnimation(_DeltaTime);
			break;
		case ESinSmallChainType::Hor:
			HorHitAnimation(_DeltaTime);
			break;
		}
	}
}

void SmallChain::VerHitAnimation(float _DeltaTime)
{
	TimeCount += _DeltaTime * 5.0f;

	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleX = ContentsHelper::LerpClampf(V_Scale.X * 1.1f, 0.0f, TimeCount);
	ImageRenderer->SetScale({ WinScale.X * ScaleX, WinScale.Y * V_Scale.Y });

	if (1.0f <= TimeCount)
	{
		TimeCount = 0.0f;
		
		switch (Phase)
		{
		case ESinPhase::Phase1:
			StateChange(ESinSmallChainState::Death);
			break;
		case ESinPhase::Phase2:
			StateChange(ESinSmallChainState::Idle);
			break;
		}
	}
}

void SmallChain::HorHitAnimation(float _DeltaTime)
{
	TimeCount += _DeltaTime * 5.0f;

	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = ContentsHelper::LerpClampf(H_Scale.Y * 1.1f, 0.0f, TimeCount);
	ImageRenderer->SetScale({ WinScale.X * H_Scale.X, WinScale.Y * ScaleY });

	if (1.0f <= TimeCount)
	{
		TimeCount = 0.0f;

		switch (Phase)
		{
		case ESinPhase::Phase1:
			StateChange(ESinSmallChainState::Death);
			break;
		case ESinPhase::Phase2:
			StateChange(ESinSmallChainState::Idle);
			break;
		}
	}
}

void SmallChain::HeroHitCheck(float _DeltaTime)
{
	if (0.0f < HitTimeCount)
	{
		FVector HeroPos = GetSinChapter()->GetPlayerHero()->GetActorLocation();
		FVector Pos = GetActorLocation();
		switch (Type)
		{
		case ESinSmallChainType::Ver:
			if (25.0f > abs(HeroPos.X - Pos.X))
			{
				GetSinChapter()->GetPlayerHero()->SinHero_StateChange(ESinHeroState::Hit);
				HitTimeCount = 0.0f;
			}
			break;
		case ESinSmallChainType::Hor:
			if (25.0f > abs(HeroPos.Y - Pos.Y))
			{
				GetSinChapter()->GetPlayerHero()->SinHero_StateChange(ESinHeroState::Hit);
				HitTimeCount = 0.0f;
			}
			break;
		}

		HitTimeCount -= _DeltaTime;
	}
}

void SmallChain::DeathStart()
{
}

void SmallChain::Death(float _DeltaTime)
{
	GetSinChapter()->M_SmallChainDeathCall(Phase1_Idx);
	Destroy();
}

void SmallChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SmallChain::MoveY_Update(float _DeltaTime)
{
	if (ESinSmallChainType::Hor == Type)
	{
		AddActorLocation({ 0.0f, GetSinChapter()->M_GetSpeedY() * _DeltaTime });
	}
}

void SmallChain::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSmallChainState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinSmallChainState::Show:
		Show(_DeltaTime);
		break;
	case ESinSmallChainState::Hit:
		Hit(_DeltaTime);
		break;
	case ESinSmallChainState::Death:
		Death(_DeltaTime);
		break;
	}
}

void SmallChain::StateChange(ESinSmallChainState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinSmallChainState::Idle:
			IdleStart();
			break;
		case ESinSmallChainState::Show:
			ShowStart();
			break;
		case ESinSmallChainState::Hit:
			HitStart();
			break;
		case ESinSmallChainState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}


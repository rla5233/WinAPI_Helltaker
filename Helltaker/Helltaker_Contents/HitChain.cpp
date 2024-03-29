#include "HitChain.h"

#include "SinChapterManager.h"
#include "HitChainHp.h"

#include <EngineBase/EngineRandom.h>

const FVector HitChain::Scale = { 0.2656f, 0.898f };
bool HitChain::IsLoad = false;
bool HitChain::IsSound = false;

const float HitChain::HitDelayTime = 0.19f;

HitChain::HitChain()
{
}

HitChain::~HitChain()
{
}

void HitChain::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LHitChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RHitChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LBrokenChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RBrokenChain.png");

		ContentsHelper::LoadSound("Sound\\Effect", "boss_big_chain_show_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_big_chain_show_002.wav");

		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_break_L.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_break_R.wav");

		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_L_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_R_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_L_002.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_R_002.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_L_003.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "boss_chain_kick_R_003.wav");

		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	IsSound = false;
}

void HitChain::IdleStart()
{
	switch (Type)
	{
	case ESinHitChainType::Left:
		ImageRenderer->SetImage("Sin_LHitChain.png");
		break;
	case ESinHitChainType::Right:
		ImageRenderer->SetImage("Sin_RHitChain.png");
		break;
	}

	if (false == IsSound)
	{
		int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 4);
		switch (RandomValue)
		{
		case 1:
			UEngineSound::SoundPlay("boss_big_chain_show_001.wav");
			break;
		case 2:
			UEngineSound::SoundPlay("boss_big_chain_show_002.wav");
			break;
		}

		IsSound = true;
	}

	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, 0.0f }, WinScale * Scale });
	FadeOutOn();
	IdleOrder = 0;
}

void HitChain::Idle(float _DeltaTime)
{
	HitDelayCheck(_DeltaTime);

	switch (IdleOrder)
	{
	case 0:
		FadeOutCheck(_DeltaTime);
		break;
	case 1:
		FadeInCheck(_DeltaTime);
		break;
	}
}

void HitChain::FadeOutCheck(float _DeltaTime)
{
	FadeOutUpdate(ImageRenderer, _DeltaTime, 1.0f, 0.6f, 0.3f);

	if (false == IsFadeOutOn())
	{
		FadeInOn();
		++IdleOrder;
	}
}

void HitChain::FadeInCheck(float _DeltaTime)
{
	FadeInUpdate(ImageRenderer, _DeltaTime, 1.0f, 0.3f, 0.6f);
	if (false == IsFadeInOn())
	{
		FadeOutOn();
		--IdleOrder;
	}
}

void HitChain::MoveStart()
{
	MoveOn();
}

void HitChain::Move(float _DeltaTime)
{
	if (true == IsMoveOn())
	{
		AddActorLocation({ 0.0f, GetSinChapter()->M_GetSpeedY() * _DeltaTime });
	}
}

void HitChain::HitStart()
{
	GetSinChapter()->GetHitChainHp()->StateChange(ESinHitChainHpState::Hit);
	ImageRenderer->SetAlpha(1.0f);
	HitSoundPlay();

	--HitCount;
	HitDelayTimeCount = HitDelayTime;
	CanHit = false;
}

void HitChain::Hit(float _DeltaTime)
{
	if (0 >= HitCount)
	{
		StateChange(ESinHitChainState::Death);
		return;
	}
	else
	{
		State = ESinHitChainState::Idle;
	}

	HitDelayCheck(_DeltaTime);
}

void HitChain::HitSoundPlay()
{
	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (Type)
	{
	case ESinHitChainType::Left:
		switch (RandomValue)
		{
		case 1:
			UEngineSound::SoundPlay("boss_chain_kick_L_001.wav").SetVolume(0.7f);
			break;
		case 2:
			UEngineSound::SoundPlay("boss_chain_kick_L_002.wav").SetVolume(0.7f);
			break;
		case 3:
			UEngineSound::SoundPlay("boss_chain_kick_L_003.wav").SetVolume(0.7f);
			break;
		}
		break;
	case ESinHitChainType::Right:
		switch (RandomValue)
		{
		case 1:
			UEngineSound::SoundPlay("boss_chain_kick_R_001.wav").SetVolume(0.7f);
			break;
		case 2:
			UEngineSound::SoundPlay("boss_chain_kick_R_002.wav").SetVolume(0.7f);
			break;
		case 3:
			UEngineSound::SoundPlay("boss_chain_kick_R_003.wav").SetVolume(0.7f);
			break;
		}
		break;
	}
}

void HitChain::HitDelayCheck(float _DeltaTime)
{
	if (false == CanHit)
	{
		HitDelayTimeCount -= _DeltaTime;

		if (0.0f >= HitDelayTimeCount)
		{
			CanHit = true;
		}
	}
}

void HitChain::DeathStart()
{
	switch (Type)
	{
	case ESinHitChainType::Left:
		ImageRenderer->SetImage("Sin_LBrokenChain.png");
		break;
	case ESinHitChainType::Right:
		ImageRenderer->SetImage("Sin_RBrokenChain.png");
		break;
	}

	DeathSoundPlay();
	FadeOutOn();
}

void HitChain::Death(float _DeltaTime)
{
	FadeOutUpdate(ImageRenderer, _DeltaTime, 1.5f);

	if (false == IsFadeOutOn())
	{
		GetSinChapter()->HitChainDeathUpdate(CurPoint);
		Destroy();
	}
}

void HitChain::DeathSoundPlay()
{
	switch (Type)
	{
	case ESinHitChainType::Left:
		UEngineSound::SoundPlay("boss_chain_break_L.wav").SetVolume(0.7f);
		break;
	case ESinHitChainType::Right:
		UEngineSound::SoundPlay("boss_chain_break_R.wav").SetVolume(0.7f);
		break;
	}
}

void HitChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void HitChain::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinHitChainState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinHitChainState::Move:
		Move(_DeltaTime);
		break;
	case ESinHitChainState::Hit:
		Hit(_DeltaTime);
		break;
	case ESinHitChainState::Death:
		Death(_DeltaTime);
		break;
	}
}

void HitChain::StateChange(ESinHitChainState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinHitChainState::Idle:
			IdleStart();
			break;
		case ESinHitChainState::Move:
			MoveStart();
			break;
		case ESinHitChainState::Hit:
			HitStart();
			break;
		case ESinHitChainState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}


#include "HitChain.h"

#include "SinChapterManager.h"

const FVector HitChain::Scale = { 0.2656f, 0.898f };
bool HitChain::IsLoad = false;

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

		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
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
	if (false == FadeOutUpdate(ImageRenderer, _DeltaTime, 1.0f, 0.7f, 0.3f))
	{
		FadeInOn();
		++IdleOrder;
	}
}

void HitChain::FadeInCheck(float _DeltaTime)
{
	if (false == FadeInUpdate(ImageRenderer, _DeltaTime, 1.0f, 0.3f, 0.7f))
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

	GetSinChapter()->HitChainDeathUpdate(CurPoint);
}

void HitChain::Death(float _DeltaTime)
{
	Destroy();
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


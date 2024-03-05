#include "HitChain.h"

#include "SinChapterManager.h"

const FVector HitChain::Scale = { 0.2656f, 0.898f };
bool HitChain::IsLoad = false;

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
}

void HitChain::Idle(float _DeltaTime)
{
	
}

void HitChain::MoveStart()
{
	//MoveOn();
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
}

void HitChain::Hit(float _DeltaTime)
{
	if (0 >= HitCount)
	{
		StateChange(ESinHitChainState::Death);
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


#include "ChainLink.h"

#include "SinChapterManager.h"

bool ChainLink::IsLoad = false;

const FVector ChainLink::Scale = { 0.0375f, 0.1388f };
const float ChainLink::SpeedY = -150.0f;

ChainLink::ChainLink()
{
}

ChainLink::~ChainLink()
{
}

void ChainLink::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LChainLink.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RChainLink.png");

		IsLoad = true;
	}

	L_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Mid);
	R_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Mid);
}

void ChainLink::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.412f;

	L_ImageRenderer->SetImage("Sin_LChainLink.png");
	L_ImageRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * Scale });

	R_ImageRenderer->SetImage("Sin_RChainLink.png");
	R_ImageRenderer->SetTransform({ { PosX, 0.0f }, WinScale * Scale });
}

void ChainLink::Idle(float _DeltaTime)
{
}

void ChainLink::MoveStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * Scale.Y;

	SetEndPosY(-(ScaleY * 0.5f));

	float ChainCount = static_cast<float>(GetSinChapter()->GetSinChainLinkSize());
	SetResetPosY(ScaleY * (ChainCount - 0.5f));

	MoveOn();
}

void ChainLink::Move(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
}

void ChainLink::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ChainLink::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinChainState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinChainState::Move:
		Move(_DeltaTime);
		break;
	}
}

void ChainLink::StateChange(ESinChainState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinChainState::Idle:
			IdleStart();
			break;
		case ESinChainState::Move:
			MoveStart();
			break;
		}
	}

	State = _State;
}
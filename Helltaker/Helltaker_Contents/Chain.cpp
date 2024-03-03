#include "Chain.h"

#include "SinChapterManager.h"

bool Chain::IsLoad = false;

const FVector Chain::Scale = { 0.0375f, 0.1388f };
const float Chain::SpeedY = -150.0f;

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::BeginPlay()
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

void Chain::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.412f;

	L_ImageRenderer->SetImage("Sin_LChainLink.png");
	L_ImageRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * Scale });

	R_ImageRenderer->SetImage("Sin_RChainLink.png");
	R_ImageRenderer->SetTransform({ { PosX, 0.0f }, WinScale * Scale });
}

void Chain::Idle(float _DeltaTime)
{
}

void Chain::MoveStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * Scale.Y;

	SetEndPosY(-(ScaleY * 0.5f));

	float ChainCount = static_cast<float>(GetSinChapter()->GetSinChainSize());
	SetResetPosY(ScaleY * (ChainCount - 0.5f));

	MoveOn();
}

void Chain::Move(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
}

void Chain::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Chain::StateUpdate(float _DeltaTime)
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

void Chain::StateChange(ESinChainState _State)
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
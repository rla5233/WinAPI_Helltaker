#include "Bridge.h"

bool Bridge::IsLoad = false;

const FVector Bridge::Scale = { 0.4912f, 0.5555f };;
const float Bridge::SpeedY = -150.0f;

Bridge::Bridge()
{
}

Bridge::~Bridge()
{
}

void Bridge::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_Bridge.png");

		IsLoad = true;
	}

	ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Mid);
}

void Bridge::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	ImageRenderer->SetImage("Sin_Bridge.png");
	ImageRenderer->SetTransform({ { 0.0f, 0.0f },  WinScale * Scale });
}

void Bridge::Idle(float _DeltaTime)
{
}

void Bridge::MoveStart()
{
	Bridge->MoveOn();

	float ScaleY = WinScale.Y * SinBridgeScale.Y;
	Bridge->SetEndPosY(-(ScaleY * 0.5f));
	Bridge->SetResetPosY(ScaleY * (static_cast<float>(SinBridge.size()) - 0.5f));
}

void Bridge::Move(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
}

void Bridge::StopStart()
{
}

void Bridge::Stop(float _DeltaTime)
{
}

void Bridge::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Bridge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinBridgeState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinBridgeState::Move:
		Move(_DeltaTime);
		break;
	case ESinBridgeState::Stop:
		Stop(_DeltaTime);
		break;
	}
}

void Bridge::StateChange(ESinBridgeState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinBridgeState::Idle:
			IdleStart();
			break;
		case ESinBridgeState::Move:
			MoveStart();
			break;
		case ESinBridgeState::Stop:
			StopStart();
			break;
		}
	}

	State = _State;
}
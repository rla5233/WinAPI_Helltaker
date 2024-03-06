#include "Bridge.h"

#include "SinChapterManager.h"

bool Bridge::IsLoad = false;

const FVector Bridge::Scale = { 0.4912f, 0.5555f };

Bridge::Bridge()
{
}

Bridge::~Bridge()
{
}

void Bridge::BeginPlay()
{
	SinMoveActor::BeginPlay();

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

	MoveOff();
}

void Bridge::Idle(float _DeltaTime)
{
}

void Bridge::MoveStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * Scale.Y;

	SetEndPosY(-(ScaleY * 0.5f));

	float BridgeCount = static_cast<float>(GetSinChapter()->GetSinBridgeSize());
	SetResetPosY(ScaleY * (BridgeCount - 0.5f));

	MoveOn();
}

void Bridge::Move(float _DeltaTime)
{
	MoveY_Update(_DeltaTime);
}

void Bridge::MoveY_Update(float _DeltaTime)
{
	if (true == IsMoveOn())
	{
		AddActorLocation({ 0.0f, GetSinChapter()->M_GetSpeedY() * _DeltaTime });

		if (GetEndPosY() >= GetActorLocation().Y)
		{
			float Diff = GetActorLocation().Y - GetEndPosY();
			SetActorLocation({ GetActorLocation().X, GetResetPosY() + Diff});
			GetSinChapter()->AddBridgeResetCount(1);
		}
	}
}

void Bridge::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

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
		}
	}

	State = _State;
}
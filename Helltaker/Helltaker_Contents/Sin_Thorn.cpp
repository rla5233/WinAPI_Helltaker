#include "Sin_Thorn.h"

bool Sin_Thorn::IsLoad = false;

const FVector Sin_Thorn::ThornScale = { 0.0479f, 0.0851f };
const float Sin_Thorn::ChangeInter = 0.05f;
const float Sin_Thorn::SpeedY = -150.0f;;

Sin_Thorn::Sin_Thorn()
{
}

Sin_Thorn::~Sin_Thorn()
{
}

void Sin_Thorn::BeginPlay()
{
	SinComponent::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
		
		// 수정 (Debug용 삭제 필요)
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

		IsLoad = true;
	}

	ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
	ImageRenderer->SetImage("Thorn_Idle.png");
	ImageRenderer->CreateAnimation("Thorn_Up", "Thorn_Up", 0, 3, ChangeInter, false);
	ImageRenderer->CreateAnimation("Thorn_Down", "Thorn_Down", 0, 4, ChangeInter, false);
}

void Sin_Thorn::Tick(float _DeltaTime)
{
	SinComponent::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Thorn::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;

	ImageRenderer->SetImage("Thorn_Idle.png");
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void Sin_Thorn::Idle(float _DeltaTime)
{
}

void Sin_Thorn::MoveStart()
{
	MoveOn();
}

void Sin_Thorn::Move(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (DownPosY >= GetActorLocation().Y)
	{
		StateChange(EThornState::Down);
	}
}

void Sin_Thorn::MoveUpdate(float _DeltaTime)
{
	if (true == IsMoveOn())
	{
		AddActorLocation({ 0.0f, SpeedY * _DeltaTime });

		if (GetEndPosY() >= GetActorLocation().Y)
		{
			float Diff = GetActorLocation().Y - GetEndPosY();
			SetActorLocation({ GetActorLocation().X, GetResetPosY() + Diff });
			StateChange(EThornState::Up);
		}
	}
}

void Sin_Thorn::UpStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;

	ImageRenderer->AnimationReset();
	ImageRenderer->ChangeAnimation("Thorn_Up");
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
	ImageRenderer->ActiveOn();
}

void Sin_Thorn::Up(float _DeltaTime)
{
	if (true == IsMoveOn())
	{
		StateChange(EThornState::Move);
	}
}

void Sin_Thorn::DownStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;

	ImageRenderer->AnimationReset();
	ImageRenderer->ChangeAnimation("Thorn_Down");
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void Sin_Thorn::Down(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (true == ImageRenderer->IsCurAnimationEnd())
	{
		ImageRenderer->ActiveOff();
	}
}

void Sin_Thorn::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EThornState::Idle:
		Idle(_DeltaTime);
		break;
	case EThornState::Move:
		Move(_DeltaTime);
		break;
	case EThornState::Up:
		Up(_DeltaTime);
		break;
	case EThornState::Down:
		Down(_DeltaTime);
		break;
	}
}

void Sin_Thorn::StateChange(EThornState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EThornState::Idle:
			IdleStart();
			break;
		case EThornState::Move:
			MoveStart();
			break;
		case EThornState::Up:
			UpStart();
			break;
		case EThornState::Down:
			DownStart();
			break;
		}
	}

	State = _State;
}

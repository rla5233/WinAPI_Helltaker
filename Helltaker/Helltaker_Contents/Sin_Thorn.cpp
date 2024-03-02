#include "Sin_Thorn.h"

bool Sin_Thorn::IsLoad = false;

const FVector Sin_Thorn::ThornScale = { 0.0479f, 0.0851f };
const float Sin_Thorn::ChangeInter = 0.05f;

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

		IsLoad = true;
	}

	ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
	ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
	ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

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

void Sin_Thorn::UpStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;

	ImageRenderer->AnimationReset();
	ImageRenderer->ChangeAnimation("Thorn_Up");
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void Sin_Thorn::Up(float _DeltaTime)
{
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
}

void Sin_Thorn::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EThornState::Idle:
		Idle(_DeltaTime);
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

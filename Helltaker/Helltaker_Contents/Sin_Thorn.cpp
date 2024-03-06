#include "Sin_Thorn.h"

#include "SinChapterManager.h"

bool Sin_Thorn::IsLoad = false;

const int Sin_Thorn::ThornCount = 7;;
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
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
		
		// 수정 (Debug용 삭제 필요)
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

		IsLoad = true;
	}

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = WinScale * ThornScale;
	float PosX = 0.0f;

	ImageRenderer.reserve(ThornCount);
	for (int i = 0; i < ThornCount; i++)
	{
		ImageRenderer.push_back(RenderActor::CreateImageRenderer(SinRenderOrder::Mid));
		ImageRenderer[i]->SetImage("Thorn_Idle.png");
		ImageRenderer[i]->CreateAnimation("Thorn_Down", "Thorn_Down", 0, 4, ChangeInter, false);
		ImageRenderer[i]->CreateAnimation("Thorn_Up", "Thorn_Up", 0, 3, ChangeInter, false);
		ImageRenderer[i]->SetTransform({{ PosX, 0.0f }, Scale });
		ImageRenderer[i]->ActiveOff();
		PosX += Scale.X * 1.088f;
	}
}

void Sin_Thorn::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Thorn::IdleStart()
{
	for (int i = 0; i < ThornCount; i++)
	{
		ImageRenderer[i]->SetImage("Thorn_Idle.png");
		ImageRenderer[i]->ActiveOn();
	}
}

void Sin_Thorn::Idle(float _DeltaTime)
{
	if (true == IsMoveOn())
	{
		StateChange(EThornState::Move);
	}
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
		AddActorLocation({ 0.0f, GetSinChapter()->M_GetSpeedY() * _DeltaTime });

		if (GetEndPosY() >= GetActorLocation().Y)
		{
			float Diff = GetActorLocation().Y - GetEndPosY();
			SetActorLocation({ GetActorLocation().X, GetResetPosY() + Diff });
			State = EThornState::Up;
		}
	}
}

void Sin_Thorn::UpStart()
{
	for (int i = 0; i < ThornCount; i++)
	{
		ImageRenderer[i]->AnimationReset();
		ImageRenderer[i]->ChangeAnimation("Thorn_Up");
		ImageRenderer[i]->ActiveOn();
	}
}

void Sin_Thorn::Up(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (UpPosY >= GetActorLocation().Y)
	{
		UpStart();
		State = EThornState::Move;
	}
}

void Sin_Thorn::DownStart()
{
	for (int i = 0; i < ThornCount; i++)
	{
		ImageRenderer[i]->AnimationReset();
		ImageRenderer[i]->ChangeAnimation("Thorn_Down");
	}
}

void Sin_Thorn::Down(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	for (int i = 0; i < ThornCount; i++)
	{
		if (true == ImageRenderer[i]->IsCurAnimationEnd())
		{
			ImageRenderer[i]->ActiveOff();
		}
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

#include "Pit.h"

#include "SinChapterManager.h"

bool Pit::IsLoad = false;

const FVector Pit::Scale = { 0.283f, 0.6074f };

Pit::Pit()
{
}

Pit::~Pit()
{
}

void Pit::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_LPit.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_RPit.png");

		IsLoad = true;
	}

	L_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::UnderBackGround);
	R_ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::UnderBackGround);
}

void Pit::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.359f;

	L_ImageRenderer->SetImage("Sin_LPit.png");
	L_ImageRenderer->SetTransform({ { -PosX, 0.0f }, WinScale * Scale });

	R_ImageRenderer->SetImage("Sin_RPit.png");
	R_ImageRenderer->SetTransform({ { PosX, 0.0f }, WinScale * Scale });
}

void Pit::Idle(float _DeltaTime)
{
}

void Pit::MoveStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * Scale.Y;
	
    SetEndPosY(-(ScaleY * 0.5f));

	float PitCount = static_cast<float>(GetSinChapter()->GetSinPitSize());
	SetResetPosY(ScaleY * (PitCount - 0.5f));
    
    MoveOn();
}

void Pit::Move(float _DeltaTime)
{
	MoveY_Update(GetSinChapter()->M_GetSpeedY() * 0.3f, _DeltaTime);
}

void Pit::StopStart()
{
}

void Pit::Stop(float _DeltaTime)
{
}

void Pit::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Pit::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinPitState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinPitState::Move:
		Move(_DeltaTime);
		break;
	case ESinPitState::Stop:
		Stop(_DeltaTime);
		break;
	}
}

void Pit::StateChange(ESinPitState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinPitState::Idle:
			IdleStart();
			break;
		case ESinPitState::Move:
			MoveStart();
			break;
		case ESinPitState::Stop:
			StopStart();
			break;
		}
	}
	
	State = _State;
}
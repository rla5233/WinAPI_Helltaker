#include "SmallChain.h"

bool SmallChain::IsLoad = false;

const FVector SmallChain::V_Scale = { 0.03f, 1.0f };
const FVector SmallChain::H_Scale = { 1.0f, 0.052f };
const float SmallChain::SpeedY = -150.0f;

SmallChain::SmallChain()
{
}

SmallChain::~SmallChain()
{
}

void SmallChain::BeginPlay()
{
	SinMoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_VChain.png");
		ContentsHelper::LoadImg("Chapter\\Component", "Sin_HChain.png");

		IsLoad = true;
	}
}

void SmallChain::CreateImageRenderer(ESinSmallChainType _Type)
{
	switch (_Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::SmallVChain);
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::Top);
		break;
	}

	Type = _Type;
}

void SmallChain::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	switch (Type)
	{
	case ESinSmallChainType::Ver:
		ImageRenderer->SetImage("Sin_VChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * V_Scale } });
		break;
	case ESinSmallChainType::Hor:
		ImageRenderer->SetImage("Sin_HChain.png");
		ImageRenderer->SetTransform({ { 0.0f, 0.0f }, { WinScale * H_Scale } });
		break;
	}

	ImageRenderer->SetAlpha(0.25);
	ImageRenderer->ActiveOff();
}

void SmallChain::Idle(float _DeltaTime)
{
}

void SmallChain::ShowStart()
{
	if (ESinSmallChainType::Hor == Type)
	{
	//	MoveOn();
	}

	ImageRenderer->ActiveOn();
	IsShow = true;
	TimeCount = 0.0f;
}

void SmallChain::Show(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
	ShowAnimation(_DeltaTime);

	if (false == IsShow)
	{
		StateChange(ESinSmallChainState::Hit);
	}
}

void SmallChain::ShowAnimation(float _DeltaTime)
{
	if (true == IsShow)
	{
		switch (Type)
		{
		case ESinSmallChainType::Ver:
			VerShowAnimation(_DeltaTime);
			break;
		case ESinSmallChainType::Hor:
			HorShowAnimation(_DeltaTime);
			break;
		}
	}
}

void SmallChain::VerShowAnimation(float _DeltaTime)
{
	if (true)
	{
		TimeCount += _DeltaTime * 3.0f;

		FVector WinScale = ContentsHelper::GetWindowScale();
		float ScaleX = ContentsHelper::LerpClampf(V_Scale.X, 0.0f, TimeCount);
		ImageRenderer->SetScale({ WinScale.X * ScaleX, WinScale.Y * V_Scale.Y });

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsShow = false;
		}
	}
}

// y축 시작 위치를 보정?
void SmallChain::HorShowAnimation(float _DeltaTime)
{
	if (true)
	{
		TimeCount += _DeltaTime * 3.0f;

		FVector WinScale = ContentsHelper::GetWindowScale();
		float ScaleY = ContentsHelper::LerpClampf(H_Scale.Y, 0.0f, TimeCount);
		ImageRenderer->SetScale({ WinScale.X * H_Scale.X, WinScale.Y * ScaleY });

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsShow = false;
		}
	}
}

void SmallChain::HitStart()
{
	ImageRenderer->SetAlpha(1);
	IsHit = true;
	TimeCount = 0.0f;
}

void SmallChain::Hit(float _DeltaTime)
{
	MoveY_Update(SpeedY, _DeltaTime);
	HitAnimation(_DeltaTime);

	if (false == IsHit)
	{
		//Destroy();
	}
}

void SmallChain::HitAnimation(float _DeltaTime)
{
	if (true == IsHit)
	{
		switch (Type)
		{
		case ESinSmallChainType::Ver:
			VerHitAnimation(_DeltaTime);
			break;
		case ESinSmallChainType::Hor:
			HorHitAnimation(_DeltaTime);
			break;
		}
	}
}

void SmallChain::VerHitAnimation(float _DeltaTime)
{
	TimeCount += _DeltaTime * 7.0f;

	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleX = ContentsHelper::LerpClampf(V_Scale.X, 0.0f, TimeCount);
	ImageRenderer->SetScale({ WinScale.X * ScaleX, WinScale.Y * V_Scale.Y });

	if (1.0f <= TimeCount)
	{
		TimeCount = 0.0f;
		IsHit = false;
	}
}

void SmallChain::HorHitAnimation(float _DeltaTime)
{
	TimeCount += _DeltaTime * 7.0f;

	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = ContentsHelper::LerpClampf(H_Scale.Y, H_Scale.Y, TimeCount);
	ImageRenderer->SetScale({ WinScale.X * H_Scale.X, WinScale.Y * ScaleY });

	if (1.0f <= TimeCount)
	{
		TimeCount = 0.0f;
		IsHit = false;
	}
}

void SmallChain::Tick(float _DeltaTime)
{
	SinMoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SmallChain::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSmallChainState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinSmallChainState::Show:
		Show(_DeltaTime);
		break;
	case ESinSmallChainState::Hit:
		Hit(_DeltaTime);
		break;
	}
}

void SmallChain::StateChange(ESinSmallChainState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinSmallChainState::Idle:
			IdleStart();
			break;
		case ESinSmallChainState::Show:
			ShowStart();
			break;
		case ESinSmallChainState::Hit:
			HitStart();
			break;
		}
	}

	State = _State;
}


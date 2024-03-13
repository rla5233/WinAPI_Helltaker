#include "BackGround.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::CreateImageRenderer(SinRenderOrder _Order)
{
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void BackGround::CreateBackGround(std::string_view _Name, EBackGroundType _Type)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.Half2D()});
	SetName(_Name);

	switch (_Type)
	{
	case EBackGroundType::Default:
		ImageRenderer = RenderActor::CreateImageRenderer(RenderOrder::BackGround);
		break;
	case EBackGroundType::Sin:
		ImageRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::BackGround);
		break;
	}
	ImageRenderer->SetImage(GetName() + ".png");
	
	FVector ImgScale = ImageRenderer->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * (ImgScale.Y / 1080) };
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void BackGround::CreateSceneBackGround(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.Half2D() });
	SetName(_Name);
	ImageRenderer = RenderActor::CreateImageRenderer(RenderOrder::SceneBackGround);
	ImageRenderer->SetImage(GetName() + ".png");

	FVector ImgScale = ImageRenderer->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * (ImgScale.Y / 1080) };
	ImageRenderer->SetTransform({ { 0, 0 }, Scale });
}

void BackGround::BackGroundChange(std::string_view _Name)
{
	ImageRenderer->SetImage(_Name);
}

void BackGround::ScaleChangeUpdate(float _DeltaTime)
{
	if (true == IsScaleChange)
	{
		ScaleChangeTime += _DeltaTime;
		
		FVector NextScale = FVector::LerpClamp(StartScale, TargetScale, ScaleChangeTime);
		ImageRenderer->SetScale(NextScale);

		if (1.0f <= ScaleChangeTime)
		{
			ScaleChangeTime = 0.0f;
			IsScaleChange = false;
		}
	}
}

void BackGround::ScaleChangeStart()
{
	IsScaleChange = true;
}

void BackGround::ScaleChange(float _DeltaTime)
{
	ScaleChangeUpdate(_DeltaTime);

	if (false == IsScaleChange)
	{
		StateChange(EBGState::None);
	}
}

void BackGround::MoveStart()
{
	IsMove = true;
}

void BackGround::Move(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (false == IsMove)
	{
		StateChange(EBGState::None);
	}
}

void BackGround::MoveUpdate(float _DeltaTime)
{
	if (true == IsMove)
	{
		MoveTime += 3.0f * _DeltaTime;

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		SetActorLocation(NextPos);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsMove = false;
		}
	}
}

void BackGround::MoveOut_YStart()
{
	StartPos = GetActorLocation();
	TargetPos = StartPos - FVector(0.0f, ImageRenderer->GetTransform().GetScale().Y);
}

void BackGround::MoveOut_Y()
{
	StateChange(EBGState::Move);
}

void BackGround::ScaleZeroY_Start()
{
	StartScale = ImageRenderer->GetTransform().GetScale();
	TargetScale = { StartScale.X, 0.0f };
}

void BackGround::ScaleZeroY()
{
	StateChange(EBGState::ScaleChange);
}

void BackGround::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void BackGround::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EBGState::ScaleChange:
		ScaleChange(_DeltaTime);
		break;
	case EBGState::Move:
		Move(_DeltaTime);
		break;
	case EBGState::MoveOut_Y:
		MoveOut_Y();
		break;
	case EBGState::ScaleZeroY:
		ScaleZeroY();
		break;
	}
}

void BackGround::StateChange(EBGState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EBGState::ScaleChange:
			ScaleChangeStart();
			break;
		case EBGState::Move:
			MoveStart();
			break;
		case EBGState::MoveOut_Y:
			MoveOut_YStart();
			break;
		case EBGState::ScaleZeroY:
			ScaleZeroY_Start();
			break;
		}
	}

	State = _State;
}

#include "MoveActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EnginePlatform/EngineInput.h>

bool MoveActor::IsLoad = false;
const float MoveActor::MoveEffectInter = 0.11f;
const float MoveActor::MoveTimeWeight = 0.17f;

MoveActor::MoveActor()
{
}

MoveActor::~MoveActor()
{}

void MoveActor::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Effect", "Move");

		IsLoad = true;
	}
}

void MoveActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MoveEffectEndCheck();
}

void MoveActor::MoveStart()
{
	MovePosCheck();
	
	CreateRandomMoveEffect();
}

void MoveActor::MovePosCheck()
{
	MoveDirCheck();

	StartPos = GetActorLocation();
	FVector TileScale = ContentsHelper::GetTileScale();

	switch (MoveDir)
	{
	case EMoveActorDir::Left:
	case EMoveActorDir::Right:
		TargetPos = StartPos + (FMoveDir * TileScale.X);
		break;
	case EMoveActorDir::Up:
	case EMoveActorDir::Down:
		TargetPos = StartPos + (FMoveDir * TileScale.Y);
		break;
	}

	MoveOn();
}

void MoveActor::MoveOneBlock(float _DeltaTime)
{
	if (true == IsMoveValue)
	{
		MoveTime += _DeltaTime;
		MoveTime += MoveTimeWeight;
		
		FVector CurLocation = GetActorLocation();

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		SetActorLocation(NextPos);

		FVector NextLocation = GetActorLocation();
		FVector Diff = NextLocation - CurLocation;

		EffectPosUpdate(Diff);
		if (PMoveDir == Point::Down || PMoveDir == Point::Up)
		{
			ChapterCameraPosUpdate(Diff);
		}		

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			CurLocationPoint += PMoveDir;
			IsMoveValue = false;
		}
	}
}

void MoveActor::MoveDirChange(EMoveActorDir _Dir)
{
	MoveDir = _Dir;
}

void MoveActor::MoveDirCheck()
{
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		PMoveDir = Point::Left;
		FMoveDir = FVector::Left;
		break;
	case EMoveActorDir::Right:
		PMoveDir = Point::Right;
		FMoveDir = FVector::Right;
		break;
	case EMoveActorDir::Up:
		PMoveDir = Point::Up;
		FMoveDir = FVector::Up;
		break;
	case EMoveActorDir::Down:
		PMoveDir = Point::Down;
		FMoveDir = FVector::Down;
		break;
	}
}

void MoveActor::SeeDirChange(EActorSeeDir _Dir)
{
	SeeDir = _Dir;
}

void MoveActor::CreateRandomMoveEffect()
{
	UImageRenderer* Renderer = CreateImageRenderer(RenderOrder::Effect);
	Renderer->SetImage("Move");

	int RandomValue = rand() % 3;

	FVector WinScale = ContentsHelper::GetWindowScale();
	switch (RandomValue)
	{
	case 0:
		Renderer->CreateAnimation("MoveEffect1", "Move", 0, 2, MoveEffectInter, false);
		Renderer->ChangeAnimation("MoveEffect1");
		break;
	case 1:
		Renderer->CreateAnimation("MoveEffect2", "Move", 3, 5, MoveEffectInter, false);
		Renderer->ChangeAnimation("MoveEffect2");
		break;
	case 2:
		Renderer->CreateAnimation("MoveEffect3", "Move", 6, 8, MoveEffectInter, false);
		Renderer->ChangeAnimation("MoveEffect3");
		break;
	}

	Renderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.036f, WinScale.Y * 0.043f } });
	
	AllMoveEffectRenderer.push_back(Renderer);
}

void MoveActor::EffectPosUpdate(const FVector& _Diff)
{
	for (UImageRenderer* Renderer : AllMoveEffectRenderer)
	{
		if (nullptr == Renderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		FVector CurPos = Renderer->GetPosition();
		Renderer->SetPosition(CurPos - _Diff);
	}
}

bool MoveActor::MoveEffectEndCheck()
{
	if (true == AllMoveEffectRenderer.empty())
	{
		return true;
	}

	if (true == AllMoveEffectRenderer.front()->IsCurAnimationEnd())
	{
		AllMoveEffectRenderer.front()->ActiveOff();
		AllMoveEffectRenderer.front()->Destroy();
		AllMoveEffectRenderer.pop_front();
	}

	return false;
}

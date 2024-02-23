#include "MoveActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EnginePlatform/EngineInput.h>

bool MoveActor::IsLoad = false;
const float MoveActor::MoveInter = 0.2f;

MoveActor::MoveActor()
{
	MoveDistanceX = ContentsHelper::GetTileScale().X;
	MoveDistanceY = ContentsHelper::GetTileScale().Y;
	Speed = ContentsHelper::GetWindowScale().X / 3.0f;
	FirstSpeed = ContentsHelper::GetWindowScale().X / 3.0f;
	Acceleration = ContentsHelper::GetWindowScale().X * 4.0f;
}

MoveActor::MoveActor(float _Speed, float _Acceleration)
	: Speed(_Speed), Acceleration(_Acceleration)
{
	MoveDistanceX = ContentsHelper::GetTileScale().X;
	MoveDistanceY = ContentsHelper::GetTileScale().Y;
	FirstSpeed = _Speed;
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

	CreateMoveEffect();
}

void MoveActor::MoveStart()
{
	MovePosCheck();
	SetRandomMoveEffect();
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
	//if (MoveDir == EMoveActorDir::Left || MoveDir == EMoveActorDir::Right)
	//{
	//	if (0.0001f < MoveDistanceX)
	//	{
	//		FVector FMoveDir = FVector(PMoveDir.X, PMoveDir.Y);
	//		FVector Diff = FMoveDir * Speed * _DeltaTime;
	//		AddActorLocation(Diff);
	//
	//		UpdateMoveEffect(Diff);
	//
	//		MoveDistanceX -= Speed * _DeltaTime;	
	//		Speed += Acceleration * _DeltaTime;
	//	}
	//	else
	//	{
	//		LocationPoint += PMoveDir;
	//		Speed = FirstSpeed;
	//
	//		FVector CurPos = GetActorLocation();
	//
	//		FVector hTileScale = { ContentsHelper::GetTileScale().Half2D()};
	//		FVector NextPos = GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale;
	//		SetActorLocation(NextPos);
	//		
	//		FVector Diff = NextPos - CurPos;
	//		UpdateMoveEffect(Diff);
	//		
	//		MoveDistanceX = ContentsHelper::GetTileScale().X;
	//		MoveOff();
	//	}
	//}
	//else if (MoveDir == EMoveActorDir::Up || MoveDir == EMoveActorDir::Down)
	//{
	//	if (0.0001f < MoveDistanceY)
	//	{
	//		FVector PrevLocation = GetActorLocation();
	//		FVector FMoveDir = FVector(PMoveDir.X, PMoveDir.Y);
	//		FVector Diff = FMoveDir * Speed * _DeltaTime;
	//		AddActorLocation(Diff);
	//
	//		UpdateMoveEffect(Diff);
	//
	//		FVector NextLocation = GetActorLocation();
	//		ChapterCameraPosUpdate(NextLocation - PrevLocation);
	//
	//		MoveDistanceY -= Speed * _DeltaTime;
	//		Speed += Acceleration * _DeltaTime;
	//	}
	//	else
	//	{
	//		LocationPoint += PMoveDir;
	//		Speed = FirstSpeed;
	//
	//		FVector PrevLocation = GetActorLocation();
	//		
	//		FVector CurPos = GetActorLocation();
	//		FVector hTileScale = { ContentsHelper::GetTileScale().Half2D() };
	//		FVector NextPos = GetChapter()->ChapterPointToLocation(LocationPoint) + hTileScale;
	//		SetActorLocation(NextPos);
	//
	//		FVector Diff = NextPos - CurPos;
	//		UpdateMoveEffect(Diff);
	//
	//		FVector NextLocation = GetActorLocation();
	//		ChapterCameraPosUpdate(NextLocation - PrevLocation);
	//
	//		MoveDistanceY = ContentsHelper::GetTileScale().Y;
	//		MoveOff();
	//	}
	//}

	if (true == IsMoveValue)
	{
		MoveTime += _DeltaTime;

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		SetActorLocation(NextPos);

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

void MoveActor::CreateMoveEffect()
{
	EffectRenderer = CreateImageRenderer(RenderOrder::Effect);
	EffectRenderer->SetImage("Move");
	EffectRenderer->CreateAnimation("MoveEffect1", "Move", 0, 2, MoveInter, false);
	EffectRenderer->CreateAnimation("MoveEffect2", "Move", 3, 5, MoveInter, false);
	EffectRenderer->CreateAnimation("MoveEffect3", "Move", 6, 8, MoveInter, false);
}

void MoveActor::SetRandomMoveEffect()
{
	int RandomValue = rand() % 2;

	FVector WinScale = ContentsHelper::GetWindowScale();
	EffectRenderer->AnimationReset();
	EffectRenderer->ChangeAnimation("MoveEffect1");
	EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.036f, WinScale.Y * 0.043f } });

	

	//switch (RandomValue)
	//{
	//case 0:
	//	EffectRenderer->ChangeAnimation("BigHit1");
	//	EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.081f, WinScale.Y * 0.186f } });
	//	break;
	//case 1:
	//	EffectRenderer->ChangeAnimation("BigHit2");
	//	EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.09f, WinScale.Y * 0.145f } });
	//	break;
	//}

	EffectRenderer->ActiveOn();
}

void MoveActor::UpdateMoveEffect(const FVector& _Diff)
{
	FVector CurPos = EffectRenderer->GetPosition();
	EffectRenderer->SetPosition(CurPos - _Diff);
}

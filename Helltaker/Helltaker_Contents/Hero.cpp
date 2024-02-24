#include "Hero.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"
#include "Skeleton.h"

#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

bool Hero::IsLoad = false;

Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::BeginPlay()
{
	MoveActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Idle");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Move");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Kick");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Victory");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Idle");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Move");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Kick");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Victory");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Death");
		ContentsHelper::LoadFolder("Effect", "Hero");
		
		IsLoad = true;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer = CreateImageRenderer(RenderOrder::Hero);
	
	ImageRenderer->SetImage("Hero_Left_Idle");
	ImageRenderer->CreateAnimation("Hero_LIdle", "Hero_Left_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Hero_LMove", "Hero_Left_Move", 0, 5, MoveInter, false);	
	ImageRenderer->CreateAnimation("Hero_LKick", "Hero_Left_Kick", 0, 12, KickInter, false);	
	ImageRenderer->CreateAnimation("Hero_LVictory", "Hero_Left_Victory", 0, 31, VictoryInter, false);
	
	ImageRenderer->CreateAnimation("Hero_RIdle", "Hero_Right_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Hero_RMove", "Hero_Right_Move", 0, 5, MoveInter, false);
	ImageRenderer->CreateAnimation("Hero_RKick", "Hero_Right_Kick", 0, 12, KickInter, false);
	ImageRenderer->CreateAnimation("Hero_RVictory", "Hero_Right_Victory", 0, 31, VictoryInter, false);
	
	ImageRenderer->CreateAnimation("Hero_Death", "Hero_Death", 0, 17, DeathInter, false);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHeroState::Idle);
}

void Hero::InputCheck(float _DeltaTime)
{
	if (false == CanActionCheck)
	{
		return;
	}

	if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
	{
		MoveDirChange(EMoveActorDir::Up);
		ActionCheck(_DeltaTime, 'W', VK_UP);
	}
	else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
	{
		MoveDirChange(EMoveActorDir::Left);
		SeeDirChange(EActorSeeDir::Left);
		ActionCheck(_DeltaTime, 'A', VK_LEFT);
	}
	else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
	{
		MoveDirChange(EMoveActorDir::Down);
		ActionCheck(_DeltaTime, 'S', VK_DOWN);
	}
	else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
	{
		MoveDirChange(EMoveActorDir::Right);
		SeeDirChange(EActorSeeDir::Right);
		ActionCheck(_DeltaTime, 'D', VK_RIGHT);
	}
	// Debug
	else if (UEngineInput::IsPress('K'))
	{
		StateChange(EHeroState::Death);
	}
	else if (UEngineInput::IsDown('C'))
	{
		CheatMode = !CheatMode;
	}
}

void Hero::ActionCheck(float _DeltaTime, int _Key1, int _Key2)
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
	Point CurPoint = GetLocationPoint();
	
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		SetNextLocationPoint(CurPoint + Point::Left);
		SeeDirChange(EActorSeeDir::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurPoint + Point::Right);
		SeeDirChange(EActorSeeDir::Right);
		break;
	case EMoveActorDir::Up:
		SetNextLocationPoint(CurPoint + Point::Up);
		break;
	case EMoveActorDir::Down:
		SetNextLocationPoint(CurPoint + Point::Down);
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	
	Point NextPoint = GetNextLocationPoint();
	if (0 <= NextPoint.Y && NextPoint.Y < Height && 0 <= NextPoint.X && NextPoint.X < Width)
	{
		if (true == Map[NextPoint.Y][NextPoint.X].IsVaild)
		{
			if (0 >= ActionPoint)
			{
				StateChange(EHeroState::Death);
				return;
			}

			NextTileCheck(NextPoint, _DeltaTime, _Key1, _Key2);
			return;
		}
	}
	
	StateChange(EHeroState::None);
	StateChange(EHeroState::Idle);
}

void Hero::NextTileCheck(Point _Point, float _DeltaTime, int _Key1, int _Key2)
{
	if (true == GetChapter()->IsLockBoxPoint() && IsHaveKey)
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Move, _DeltaTime);
		GetChapter()->DeleteLockBox();
		return;
	}

	if (nullptr == GetChapter()->M_GetHitActor(_Point))
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Move, _DeltaTime);

		if (true == GetChapter()->IsKeyPoint())
		{
			GetChapter()->DeleteKey();
			IsHaveKey = true;
		}
	}
	else
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Kick, _DeltaTime, _Key1, _Key2);
	}
}

void Hero::ThornHitCheck(EHeroState _State)
{
	// Dubug
	if (true == CheatMode)
	{
		return;
	}

	Point CurPoint  = GetLocationPoint();
	Point NextPoint = GetNextLocationPoint();
	switch (_State)
	{
	case EHeroState::Move:
		if (true == GetChapter()->GetTileInfoVec()[NextPoint.Y][NextPoint.X].IsThorn)
		{
			--ActionPoint;
		}
		break;
	case EHeroState::Kick:
		if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
		{
			--ActionPoint;
		}
		break;
	}
}

void Hero::Idle(float _DeltaTime)
{
	InputCheck(_DeltaTime);
}

void Hero::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * IdleScale } });
	CanActionCheck = true;

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Hero_LIdle");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Hero_RIdle");
		break;
	}
}

void Hero::Move(float _DeltaTime)
{
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		StateChange(EHeroState::Idle);
	}
}

void Hero::MoveStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * MoveScale } });
	CanActionCheck = false;

	GetChapter()->M_ChangeThornState();
	ThornHitCheck(EHeroState::Move);

	UpdateActionPoint();
	GetChapter()->M_UpdateHeroActionPoint();

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Hero_LMove");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Hero_RMove");
		break;
	}

	MoveActor::MoveStart();
}

void Hero::Kick(float _DeltaTime)
{
	InputCheck(_DeltaTime);

	if (true == ImageRenderer->IsCurAnimationEnd())
	{
		StateChange(EHeroState::Idle);
		return;
	}
	
	if (6 == ImageRenderer->GetCurAnimationImageFrame())
	{
		CanActionCheck = true;
	}
}

void Hero::KickStart(float _DeltaTime, int _Key1, int _Key2)
{

	if (0 < KickDelayTimeCount)
	{ 
		KickDelayTimeCount -= _DeltaTime;
		return;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * KickScale } });
	CanActionCheck = false;
	KickDelayTimeCount = KickDelayTime;

	GetChapter()->M_ChangeThornState();
	ThornHitCheck(EHeroState::Kick);

	UpdateActionPoint();
	GetChapter()->M_UpdateHeroActionPoint();

	Point NextPoint = GetNextLocationPoint();
	HitActor* Other = GetChapter()->M_GetHitActor(NextPoint);
	Other->NextStateCheck(MoveDir);	

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_LKick");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_RKick");
		break;
	}
}

void Hero::Victory(float _DeltaTime)
{
}

void Hero::VictoryStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.375f) }, { TileScale * VictoryScale } });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Hero_LVictory");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Hero_RVictory");
		break;
	}
}

void Hero::Death(float _DeltaTime)
{

}

void Hero::DeathStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ {0.0f, (WinScale.Y * 1.15f) * (-0.25f)}, {WinScale.X * 0.375f, WinScale.Y * 1.15f} });
	ImageRenderer->ChangeAnimation("Hero_Death");
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Hero::ChapterCameraPosUpdate(const FVector& _Diff)
{
	MoveActor::ChapterCameraPosUpdate(_Diff);

	GetChapter()->CameraPosUpdate(_Diff);
}

void Hero::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EHeroState::Idle:
		Idle(_DeltaTime);
		break;
	case EHeroState::Move:
		Move(_DeltaTime);
		break;
	case EHeroState::Kick:
		Kick(_DeltaTime);
		break;
	case EHeroState::Victory:
		Victory(_DeltaTime);
		break;
	case EHeroState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Hero::StateChange(EHeroState _State, float _DeltaTime, int _Key1, int _Key2)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EHeroState::Idle:
			IdleStart();
			break;
		case EHeroState::Move:
			MoveStart();
			break;
		case EHeroState::Kick:
			KickStart(_DeltaTime, _Key1, _Key2);
			break;
		case EHeroState::Victory:
			VictoryStart();
			break;
		case EHeroState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}

// Debug
void Hero::UpdateActionPoint()
{
	// Debug
	if (true == CheatMode)
	{
		return;
	}

	--ActionPoint;
}

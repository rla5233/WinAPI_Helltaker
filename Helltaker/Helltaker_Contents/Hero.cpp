#include "Hero.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"
#include "Skeleton.h"

#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

bool Hero::IsLoad = false;

Hero::Hero()
	: MoveActor(ContentsHelper::GetWindowScale().X * 0.09f, ContentsHelper::GetWindowScale().X * 4.0f)
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
		
		IsLoad = true;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	Renderer = CreateImageRenderer(RenderOrder::Hero);
	
	Renderer->SetImage("Hero_Left_Idle");
	Renderer->CreateAnimation("Hero_LIdle", "Hero_Left_Idle", 0, 11, IdleInter, true);
	Renderer->CreateAnimation("Hero_LMove", "Hero_Left_Move", 0, 5, MoveInter, false);	
	Renderer->CreateAnimation("Hero_LKick", "Hero_Left_Kick", 0, 12, KickInter, false);	
	Renderer->CreateAnimation("Hero_LVictory", "Hero_Left_Victory", 0, 20, VictoryInter, false);
	
	Renderer->CreateAnimation("Hero_RIdle", "Hero_Right_Idle", 0, 11, IdleInter, true);	
	Renderer->CreateAnimation("Hero_RMove", "Hero_Right_Move", 0, 5, MoveInter, false);	
	Renderer->CreateAnimation("Hero_RKick", "Hero_Right_Kick", 0, 12, KickInter, false);	
	Renderer->CreateAnimation("Hero_RVictory", "Hero_Right_Victory", 0, 20, VictoryInter, false);
	
	Renderer->CreateAnimation("Hero_Death", "Hero_Death", 0, 17, 0.07f, false);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHeroState::Idle);
}

void Hero::ActionCheck(float _DeltaTime, int _Key1, int _Key2)
{
	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetChapterInfoVec();
	FVector CurLocationPoint = GetLocationPoint();
	
	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		SetNextLocationPoint(CurLocationPoint + FVector::Left);
		SeeDirChange(EActorSeeDir::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurLocationPoint + FVector::Right);
		SeeDirChange(EActorSeeDir::Right);
		break;
	case EMoveActorDir::Up:
		SetNextLocationPoint(CurLocationPoint + FVector::Up);
		break;
	case EMoveActorDir::Down:
		SetNextLocationPoint(CurLocationPoint + FVector::Down);
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	int Next_X = GetNextLocationPoint().iX();
	int Next_Y = GetNextLocationPoint().iY();
	if (0 <= Next_Y && Next_Y < Height && 0 <= Next_X && Next_X < Width)
	{
		if (true == Map[Next_Y][Next_X].IsVaild)
		{
			NextTileCheck(Next_X, Next_Y, _DeltaTime, _Key1, _Key2);
			return;
		}
	}
	
	StateChange(EHeroState::None);
	StateChange(EHeroState::Idle);
}

void Hero::NextTileCheck(int _X, int _Y, float _DeltaTime, int _Key1, int _Key2)
{
	if (nullptr == GetChapter()->GetHitActor(_X, _Y))
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Move, _DeltaTime);
	}
	else
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Kick, _DeltaTime, _Key1, _Key2);
	}
}

void Hero::Idle(float _DeltaTime)
{
}

void Hero::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Renderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * IdleScale } });
	CanActionCheck = true;

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Hero_LIdle");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Hero_RIdle");
		break;
	}
}

void Hero::Move(float _DeltaTime)
{
	if (true == IsMove())
	{
		MoveOneBlock(_DeltaTime);
	}

	if (false == IsMove())
	{
		StateChange(EHeroState::Idle);
	}
}

void Hero::MoveStart(float _DeltaTime)
{
	if (0 < MoveDelayTimeCount)
	{
		MoveDelayTimeCount -= _DeltaTime;
		return;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	Renderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * MoveScale } });
	MoveDelayTimeCount = MoveDelayTime;
	CanActionCheck = false;
	GetChapter()->ChangeThornState();

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Hero_LMove");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Hero_RMove");
		break;
	}

	MoveOn();
}

void Hero::Kick(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		StateChange(EHeroState::Idle);
		return;
	}
	
	if (6 == Renderer->GetCurAnimationImageFrame())
	{
		CanActionCheck = true;
	}
}

void Hero::KickStart(float _DeltaTime, int _Key1, int _Key2)
{
	if (UEngineInput::IsPress(_Key1) || UEngineInput::IsPress(_Key2))
	{
		if (0 < KickDelayTimeCount)
		{ 
			KickDelayTimeCount -= _DeltaTime;
			return;
		}

		FVector TileScale = ContentsHelper::GetTileScale();
		Renderer->SetTransform({ { 0.0f, TileScale.Y * (-0.225f) }, { TileScale * KickScale } });
		CanActionCheck = false;
		KickDelayTimeCount = KickDelayTime;
		GetChapter()->ChangeThornState();

		// Skeleton, Stone 업 캐스팅
		FVector NextLocationPoint = GetNextLocationPoint();
		HitActor* Other = GetChapter()->GetHitActor(NextLocationPoint.iX(), NextLocationPoint.iY());
		Other->NextStateCheck(MoveDir);	

		switch (SeeDir)
		{
		case EActorSeeDir::Left:
			Renderer->AnimationReset();
			Renderer->ChangeAnimation("Hero_LKick");
			break;
		case EActorSeeDir::Right:
			Renderer->AnimationReset();
			Renderer->ChangeAnimation("Hero_RKick");
			break;
		}
	}
}

void Hero::Victory(float _DeltaTime)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	float Diff_Y = TileScale.Y * (IdleScale.Y - VictoryScale.Y) / 2.0f;
	Renderer->SetTransform({ {0.0f, Diff_Y}, {TileScale * VictoryScale} });

	if (0 > VictoryTimeCount)
	{
		VictoryTimeCount = VictoryTime;
		return;
	}

	VictoryTimeCount -= _DeltaTime;
}

void Hero::VictoryStart()
{
	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		Renderer->ChangeAnimation("Hero_LVictory");
		break;
	case EActorSeeDir::Right:
		Renderer->ChangeAnimation("Hero_RVictory");
		break;
	}
}

void Hero::Death(float _DeltaTime)
{
}

void Hero::DeathStart()
{

}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
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
			MoveStart(_DeltaTime);
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
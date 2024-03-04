#include "Sin_Hero.h"

#include "Sin_Thorn.h"
#include "SinChapterManager.h"

Sin_Hero::Sin_Hero()
{
}

Sin_Hero::~Sin_Hero()
{
}

void Sin_Hero::ActionCheck()
{
	if (-3 == PointX && EMoveActorDir::Left != GetMoveDir())
	{
		StateChange(EHeroState::Move);
	}
	else if (3 == PointX && EMoveActorDir::Right != GetMoveDir())
	{
		StateChange(EHeroState::Move);
	}
	else if (-3 < PointX && 3 > PointX)
	{
		StateChange(EHeroState::Move);
	}
}

void Sin_Hero::MoveStart()
{
	HeroBase::MoveStart();

	PointXUpdate();
	SetTargetPosY();

	CreateRandomMoveEffect(EChapterType::Sin);
}

void Sin_Hero::SetTargetPosY()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float ScaleY = WinScale.Y * Sin_Thorn::GetThornScale().Y * 1.1f;

	switch (GetMoveDir())
	{
	case EMoveActorDir::Up:
	case EMoveActorDir::Down:
		SetTargetPos(GetStartPos() + (GetFMoveDir() * ScaleY));
		break;
	}
}

void Sin_Hero::PointXUpdate()
{
	switch (GetMoveDir())
	{
	case EMoveActorDir::Right:
		++PointX;
		break;
	case EMoveActorDir::Left:
		--PointX;
		break;
	}
}

void Sin_Hero::KickCheck()
{
	HeroBase::KickCheck();

}

void Sin_Hero::ThornHitCheck()
{
	HeroBase::ThornHitCheck();

}

void Sin_Hero::IdleStart()
{
}

void Sin_Hero::Idle(float _DeltaTime)
{
}

void Sin_Hero::MoveYStart()
{
	IsMoveY = true;
}

void Sin_Hero::MoveY(float _DeltaTime)
{
	MoveY_Update(_DeltaTime);
}

void Sin_Hero::MoveY_Update(float _DeltaTime)
{
	if (true == IsMoveY)
	{ 
		float SpeedY = SinChapterManager::M_GetSpeedY();
		AddTargetPos({ 0.0f, SpeedY * _DeltaTime });
		AddActorLocation({ 0.0f, SpeedY * _DeltaTime });
	}
}

void Sin_Hero::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
	
	HeroBase::Tick(_DeltaTime);
}

void Sin_Hero::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinHeroState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinHeroState::MoveY:
		MoveY(_DeltaTime);
		break;
	}
}

void Sin_Hero::SinHero_StateChange(ESinHeroState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinHeroState::Idle:
			IdleStart();
			break;
		case ESinHeroState::MoveY:
			MoveYStart();
			break;
		}
	}

	State = _State;
}

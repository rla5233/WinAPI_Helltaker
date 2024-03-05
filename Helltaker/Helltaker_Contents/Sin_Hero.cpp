#include "Sin_Hero.h"

#include "HeroLife.h"
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
	if (0 == CurPoint.X)
	{
		switch (GetMoveDir())
		{
		case EMoveActorDir::Left:
			HitChainCheck();
			break;
		default:
			StateChange(EHeroState::Move);
			break;
		}
	}
	else if (6 == CurPoint.X)
	{
		switch (GetMoveDir())
		{
		case EMoveActorDir::Right:
			HitChainCheck();
			break;
		default:
			StateChange(EHeroState::Move);
			break;
		}
	}
	else if (0 < CurPoint.X && 6 > CurPoint.X)
	{
		StateChange(EHeroState::Move);
	}
}

void Sin_Hero::MoveStart()
{
	HeroBase::MoveStart();

	CurPointUpdate();
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

void Sin_Hero::CurPointUpdate()
{
	switch (GetMoveDir())
	{
	case EMoveActorDir::Right:
		++CurPoint.X;
		break;
	case EMoveActorDir::Left:
		--CurPoint.X;
		break;
	}
}

// 수정 (HitChain 딜레이 필요)
void Sin_Hero::HitChainCheck()
{
	UpdateCurPosY();
	if (true == GetSinChapter()->HitChainHitCheck(CurPoint))
	{
		StateChange(EHeroState::None);
		StateChange(EHeroState::Kick);
	}
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
		float SpeedY = GetSinChapter()->M_GetSpeedY();
		AddTargetPos({ 0.0f, SpeedY * _DeltaTime });
		AddActorLocation({ 0.0f, SpeedY * _DeltaTime });
	}
}

void Sin_Hero::HitStart()
{
	CreateRandomHitEffect();
	--Life;

	if (0 >= Life)
	{
		StateChange(EHeroState::Death);
		return;
	}

	GetSinChapter()->GetSinHeroLife()->StateChange(ESinHeroLifeState::HeroHit);
}

void Sin_Hero::Hit(float _DeltaTime)
{
	if (true == IsMoveY)
	{
		SinHero_StateChange(ESinHeroState::MoveY);
	}
	else
	{
		SinHero_StateChange(ESinHeroState::Idle);
	}
}

void Sin_Hero::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	if (UEngineInput::IsDown('H'))
	{
		SinHero_StateChange(ESinHeroState::Hit);
	}
	
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
	case ESinHeroState::Hit:
		Hit(_DeltaTime);
		break;
	}
}

void Sin_Hero::UpdateCurPosY()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = GetActorLocation();
	float StartPosY = SinChapterManager::GetStartPosY() * WinScale.Y;
	float ScaleY = Sin_Thorn::GetThornScale().Y * WinScale.Y;

	CurPoint.Y = std::lround((CurPos.Y - StartPosY) / ScaleY);
}

void Sin_Hero::Phase2_Start()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = GetActorLocation();
	float StartPosY = SinChapterManager::GetStartPosY() * WinScale.Y;
	float ScaleY = Sin_Thorn::GetThornScale().Y * WinScale.Y;

	CurPoint.Y = std::lround((CurPos.Y - StartPosY) / ScaleY);
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
		case ESinHeroState::Hit:
			HitStart();
			break;
		}
	}

	State = _State;
}

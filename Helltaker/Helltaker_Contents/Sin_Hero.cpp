#include "Sin_Hero.h"

const float Sin_Hero::SpeedY = -150.0f;

Sin_Hero::Sin_Hero()
{
}

Sin_Hero::~Sin_Hero()
{
}

void Sin_Hero::ActionCheck()
{
	StateChange(EHeroState::Move);
}

void Sin_Hero::MoveStart()
{
	HeroBase::MoveStart();

	CreateRandomMoveEffect(EChapterType::Sin);
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
}

void Sin_Hero::MoveY(float _DeltaTime)
{
}

void Sin_Hero::MoveY_Update(float _DeltaTime)
{
}

void Sin_Hero::Tick(float _DeltaTime)
{
	HeroBase::Tick(_DeltaTime);

	MoveY_Update(_DeltaTime);
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

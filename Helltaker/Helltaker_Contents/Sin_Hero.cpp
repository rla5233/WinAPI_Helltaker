#include "Sin_Hero.h"

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
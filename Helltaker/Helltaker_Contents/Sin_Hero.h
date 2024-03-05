#pragma once

#include "HeroBase.h"

// Ό³Έν :
class Sin_Hero : public HeroBase
{
public:
	// constructor destructor
	Sin_Hero();
	~Sin_Hero();
	
	// delete Function
	Sin_Hero(const Sin_Hero& _Other) = delete;
	Sin_Hero(Sin_Hero&& _Other) noexcept = delete;
	Sin_Hero& operator=(const Sin_Hero& _Other) = delete;
	Sin_Hero& operator=(Sin_Hero&& _Other) noexcept = delete;

	void MoveY_On()
	{
		IsMoveY = true;
	}

	int GetLife() const
	{
		return Life;
	}

	void SinHero_StateChange(ESinHeroState _State);

protected:
	void Tick(float _DeltaTime);

	void MoveStart() override;

	void ActionCheck() override;
	void KickCheck() override;

	void ThornHitCheck() override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveYStart();
	void SetTargetPosY();
	void MoveY(float _DeltaTime);

	void PointXUpdate();
	void MoveY_Update(float _DeltaTime);

	void HitStart();
	void Hit(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	bool IsMoveY = false;
	int PointX = 0;
	int Life = 4;

	ESinHeroState State = ESinHeroState::None;
};


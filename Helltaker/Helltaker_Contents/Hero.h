#pragma once

#include "HeroBase.h"

class Hero : public HeroBase
{
public:
	// constrcuter destructer
	Hero();
	~Hero();

	// delete Function
	Hero(const Hero& _Other) = delete;
	Hero(Hero&& _Other) noexcept = delete;
	Hero& operator=(const Hero& _Other) = delete;
	Hero& operator=(Hero&& _Other) noexcept = delete;

	int GetActionPoint() const
	{
		return ActionPoint;
	}

	void SetActionPoint(int _Value)
	{
		ActionPoint = _Value;
	}

	void UpdateActionPoint();

protected:
	void MoveStart() override;
	void Move(float _DeltaTime) override;

	void KickStart() override;
	
	void DeathStart() override;

private:
	void ThornHitCheck() override;
	void ActionCheck();
	void KickCheck() override;
	void NextTileCheck(Point _Point);

private:
	int ActionPoint = -1;
	bool IsHaveKey = false;
	
	static bool IsLoad;
};
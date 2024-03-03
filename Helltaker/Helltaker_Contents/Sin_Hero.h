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


protected:
	void MoveStart() override;

	void ActionCheck(float _DeltaTime, int _Key1, int _Key2) override;
	void KickCheck() override;

private:

};


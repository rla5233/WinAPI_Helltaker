#pragma once

#include "RenderActor.h"

// Ό³Έν :
class HeroLife : RenderActor
{
public:
	// constructor destructor
	HeroLife();
	~HeroLife();
	
	// delete Function
	HeroLife(const HeroLife& _Other) = delete;
	HeroLife(HeroLife&& _Other) noexcept = delete;
	HeroLife& operator=(const HeroLife& _Other) = delete;
	HeroLife& operator=(HeroLife&& _Other) noexcept = delete;


protected:

private:



	static bool IsLoad;
};


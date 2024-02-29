#pragma once



// Ό³Έν :
class HeroBase
{
public:
	// constructor destructor
	HeroBase();
	~HeroBase();
	
	// delete Function
	HeroBase(const HeroBase& _Other) = delete;
	HeroBase(HeroBase&& _Other) noexcept = delete;
	HeroBase& operator=(const HeroBase& _Other) = delete;
	HeroBase& operator=(HeroBase&& _Other) noexcept = delete;


protected:

private:

};


#pragma once

// Ό³Έν :
class Pit
{
public:
	// constructor destructor
	Pit();
	~Pit();
	
	// delete Function
	Pit(const Pit& _Other) = delete;
	Pit(Pit&& _Other) noexcept = delete;
	Pit& operator=(const Pit& _Other) = delete;
	Pit& operator=(Pit&& _Other) noexcept = delete;


protected:

private:

};


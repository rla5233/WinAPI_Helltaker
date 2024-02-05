#pragma once

#include <EngineCore/Level.h>

// Ό³Έν :
class Title : public ULevel
{
public:
	// constructor destructor
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

private:

};

#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class UI : public AActor
{
public:
	// constructor destructor
	UI();
	~UI();

	// delete Function
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;

protected:

private:
	UImageRenderer* Renderer = nullptr;

};

#pragma once

#include "RenderActor.h"

// Ό³Έν :
class KeyComponent : public RenderActor
{
public:
	// constructor destructor
	KeyComponent();
	~KeyComponent();

	// delete Function
	KeyComponent(const KeyComponent& _Other) = delete;
	KeyComponent(KeyComponent&& _Other) noexcept = delete;
	KeyComponent& operator=(const KeyComponent& _Other) = delete;
	KeyComponent& operator=(KeyComponent&& _Other) noexcept = delete;

	
protected:

private:
	UImageRenderer* ImageRenderer = nullptr;

};

#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Chain : public RenderActor
{
public:
	// constructor destructor
	Chain();
	~Chain();
	
	// delete Function
	Chain(const Chain& _Other) = delete;
	Chain(Chain&& _Other) noexcept = delete;
	Chain& operator=(const Chain& _Other) = delete;
	Chain& operator=(Chain&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ImageRenderer = nullptr;

	static bool IsLoad;
};


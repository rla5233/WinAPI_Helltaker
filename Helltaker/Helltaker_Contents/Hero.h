#pragma once
#include "MoveActor.h"

class Hero : public MoveActor
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

public:

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;


	int ActionPoint = 25;
};


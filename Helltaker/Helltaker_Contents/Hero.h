#pragma once
#include "MoveActor.h"
#include "RenderActor.h"

class Hero : public MoveActor, public RenderActor
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
	void LoadRenderImage(std::string_view _Name) override;
	void SetRenderImage(std::string_view _Name) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int ActionPoint = 25;

};


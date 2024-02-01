#pragma once
#include "MoveActor.h"
#include "RenderActor.h"

// ���� :
class Skeleton : public MoveActor, public RenderActor
{
public:
	// constructor destructor
	Skeleton();
	~Skeleton();

	// delete Function
	Skeleton(const Skeleton& _Other) = delete;
	Skeleton(Skeleton&& _Other) noexcept = delete;
	Skeleton& operator=(const Skeleton& _Other) = delete;
	Skeleton& operator=(Skeleton&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

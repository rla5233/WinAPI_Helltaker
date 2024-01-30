#pragma once
#include <EngineCore\Actor.h>

// 설명 : 플레이어 클래스
class Player : public AActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	
public:
	void MoveCheck(float _DeltaTime);
	void MoveOneBlock(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* PlayerRenderer = nullptr;

	const float OneMoveDistance = 60.0f;
	float MoveDistance = OneMoveDistance;
	float Speed = 500.0f;
	FVector MoveDir = FVector::Zero;

	bool IsMoving = false;
	int ActionPoint = 25;
};


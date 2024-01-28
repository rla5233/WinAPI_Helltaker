#include "Player.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>

Player::Player()
{}

Player::~Player()
{}

void Player::BeginPlay()
{
	PlayerRenderer = CreateImageRenderer(0);
	PlayerRenderer->SetPosition({ 100, 100 });
	PlayerRenderer->SetScale({ 50, 50 });
}

void Player::Tick(float _DeltaTime)
{
	MoveCheck(_DeltaTime);
}

void Player::MoveCheck(float _DeltaTime)
{
	if (false == IsMoving)
	{
		if (true == EngineInput::IsPress('A'))
		{
			MoveDir = FVector::Left;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('D'))
		{
			MoveDir = FVector::Right;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('W'))
		{
			MoveDir = FVector::Up;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('S'))
		{
			MoveDir = FVector::Down;
			IsMoving = true;
		}
	}
	else
	{
		MoveOneBlock(_DeltaTime);
	}
}

void Player::MoveOneBlock(float _DeltaTime)
{
	if (0 <= MoveDistance)
	{
		AddActorLocation(MoveDir * Speed * _DeltaTime);
		MoveDistance -= Speed * _DeltaTime;
	}
	else
	{
		MoveDistance = OneMoveDistance;
		IsMoving = false;
	}
}
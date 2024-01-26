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
	if (true == EngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}


	if (true == EngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}		
}
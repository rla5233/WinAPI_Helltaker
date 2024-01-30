#include "Player.h"

#include <EngineCore/EngineCore.h>



Player::Player()
{}

Player::~Player()
{}

void Player::BeginPlay()
{
	PlayerRenderer = CreateImageRenderer(0);
	PlayerRenderer->SetImageToScale("Hero0022.png");
	//PlayerRenderer->SetScale({ 50, 50 });
}

void Player::Tick(float _DeltaTime)
{
	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::SetImageRendererMove()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = ImageRenderer->GetPosition();

	StartPos = CurPos + FVector(WinScale.X * 0.08f, 0.0f);
	TargetPos = CurPos;

	ImgMoveOn();
}

void Character::IdleStart()
{}

void Character::Idle(float _DeltaTime)
{}

void Character::AppearStart()
{
	SetImageRendererMove();
	FadeInOn();
}

void Character::Appear(float _DeltaTime)
{
	FadeInUpdate(ImageRenderer, _DeltaTime, 4.0f);
	ImgMoveUpdate(ImageRenderer, StartPos, TargetPos, _DeltaTime, 4.0f);

	if (false == IsFadeInOn() && false == IsImgMoveOn())
	{
		StateChange(ECharacterState::Idle);
	}
}

void Character::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Character::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ECharacterState::Idle:
		Idle(_DeltaTime);
		break;
	case ECharacterState::Appear:
		Appear(_DeltaTime);
		break;
	}
}

void Character::StateChange(ECharacterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ECharacterState::Idle:
			IdleStart();
			break;
		case ECharacterState::Appear:
			AppearStart();
			break;
		}
	}

	State = _State;
}


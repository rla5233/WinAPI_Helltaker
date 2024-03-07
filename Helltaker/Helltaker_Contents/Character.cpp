#include "Character.h"

#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Character::Character()
{
}

Character::~Character()
{
}

void Character::CreateImageRenderer(RenderOrder _Order)
{
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void Character::CreateNameRenderer(RenderOrder _Order)
{
	NameRenderer = RenderActor::CreateImageRenderer(_Order);
}

void Character::ImageRendererMoveUpdate(float _DeltaTime, float _TimeWeight/* = 4.0f */)
{
	if (true == IsImageMoveValue)
	{
		MoveTime += _DeltaTime * _TimeWeight;

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		ImageRenderer->SetPosition(NextPos);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsImageMoveValue = false;
		}
	}
}

void Character::ImageRendererFadeInOn()
{
	ImageRenderer->SetAlpha(0.0f);
	FadeInOn();
}

bool Character::ImageRendererFadeInUpdate(float _DeltaTime, float _TimeWeight)
{
	return RenderActor::FadeInUpdate(ImageRenderer, _DeltaTime, _TimeWeight);
}

void Character::IdleStart()
{}

void Character::Idle(float _DeltaTime)
{}

void Character::AppearStart()
{
	ImageRendererFadeInOn();
}

void Character::Appear(float _DeltaTime)
{
	ImageRendererMoveUpdate(_DeltaTime);

	if (false == FadeInUpdate(ImageRenderer, _DeltaTime, 4.0f) && false == IsImageMoveValue)
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


#include "KeyComponent.h"

bool KeyComponent::IsLoad = false;
const FVector KeyComponent::IdleScale = { 0.5f, 0.5f };
const float KeyComponent::IdleInter = 0.2f;

KeyComponent::KeyComponent()
{
}

KeyComponent::~KeyComponent()
{
}

void KeyComponent::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Component", "Key");
		ContentsHelper::LoadImg("Chapter\\Component", "LockBox.png");
		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(RenderOrder::RenderActor);
	ImageRenderer->SetImage("LockBox.png");
	ImageRenderer->CreateAnimation("Key_Idle", "Key", 0, 11, IdleInter, true);
}

void KeyComponent::Idle(float _DeltaTime)
{

}

void KeyComponent::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();

	switch (Type)
	{
	case EKeyComponentType::Key:
		ImageRenderer->SetTransform({ { 0, 0 }, { TileScale * IdleScale } });
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Key_Idle");
		break;
	case EKeyComponentType::LockBox:
		ImageRenderer->SetTransform({ { 0, 0 }, { TileScale * IdleScale } });
		ImageRenderer->SetImage("LockBox.png");
		break;
	}
}

void KeyComponent::Death(float _DeltaTime)
{

}

void KeyComponent::DeathStart()
{

}

void KeyComponent::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void KeyComponent::StateUpdate(float _DeltaTime)
{

}

void KeyComponent::StateChange(EKeyComponentState _State)
{
	if (State != _State)
	{
		switch (State)
		{
		case EKeyComponentState::Idle:
			IdleStart();
			break;
		case EKeyComponentState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}
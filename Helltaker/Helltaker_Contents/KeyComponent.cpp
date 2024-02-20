#include "KeyComponent.h"

bool KeyComponent::IsLoad = false;
const float KeyComponent::IdleInter = 0.06f;

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
{}

void KeyComponent::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	FVector WinScale = ContentsHelper::GetWindowScale();

	switch (Type)
	{
	case EKeyComponentType::Key:
		ImageRenderer->SetTransform({ { TileScale.X * 0.07f, TileScale.Y * (-0.2f) }, {WinScale.X * 0.0437f, WinScale.Y * 0.0852f}});
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Key_Idle");
		break;
	case EKeyComponentType::LockBox:
		ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.2f)}, { WinScale.X * 0.0505f, WinScale.Y * 0.0888f}});
		ImageRenderer->SetImage("LockBox.png");
		break;
	}
}

void KeyComponent::Death(float _DeltaTime)
{
	Destroy();
}

void KeyComponent::DeathStart()
{

}


void KeyComponent::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	switch (Type)
	{
	case EKeyComponentType::Key:

		break;
	case EKeyComponentType::LockBox:
		
		break;
	}
}

void KeyComponent::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void KeyComponent::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EKeyComponentState::Idle:
		Idle(_DeltaTime);
		break;
	case EKeyComponentState::Death:
		Death(_DeltaTime);
		break;
	}
}

void KeyComponent::StateChange(EKeyComponentState _State)
{
	if (State != _State)
	{
		switch (_State)
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
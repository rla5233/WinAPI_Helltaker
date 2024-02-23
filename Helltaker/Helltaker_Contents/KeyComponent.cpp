#include "KeyComponent.h"

bool KeyComponent::IsLoad = false;
const float KeyComponent::Key_IdleInter = 0.06f;
const float KeyComponent::Death_EffectInter = 0.06f;

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
		ContentsHelper::LoadFolder("Effect", "KeyComp");

		IsLoad = true;
	}
}

void KeyComponent::Idle(float _DeltaTime)
{}

void KeyComponent::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer = CreateImageRenderer(RenderOrder::RenderActor);

	switch (Type)
	{
	case EKeyComponentType::Key:
		ImageRenderer->SetTransform({ { TileScale.X * 0.07f, TileScale.Y * (-0.2f) }, {WinScale.X * 0.0437f, WinScale.Y * 0.0852f}});
		ImageRenderer->SetImage("LockBox.png");
		ImageRenderer->CreateAnimation("Key_Idle", "Key", 0, 11, Key_IdleInter, true);
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Key_Idle");
		break;
	case EKeyComponentType::LockBox:
		ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.17f)}, { WinScale.X * 0.0505f, WinScale.Y * 0.0888f}});
		ImageRenderer->SetImage("LockBox.png");
		break;
	}
}

void KeyComponent::Death(float _DeltaTime)
{
	if (true == EffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void KeyComponent::DeathStart()
{
	ImageRenderer->ActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	EffectRenderer = CreateImageRenderer(RenderOrder::Effect);
	EffectRenderer->SetImage("KeyComp");
	EffectRenderer->SetTransform({ { 0 , 0 }, { WinScale.X * 0.165f, WinScale.Y * 0.278f } });
	EffectRenderer->CreateAnimation("KeyComp_Death", "KeyComp", 0, 8, Death_EffectInter, false);
	EffectRenderer->ChangeAnimation("KeyComp_Death");

	if (EKeyComponentType::LockBox == Type)
	{
		HitActorInfoUpdate(EHitActorState::Death);
	}

	InformDestroytoChapter();
}

void KeyComponent::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	switch (Type)
	{
	case EKeyComponentType::LockBox:
		//StateChange(EKeyComponentState::Hit);
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
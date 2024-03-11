#include "Character.h"

bool Character::IsLoad = false; 

Character::Character()
{
}

Character::~Character()
{
}

void Character::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters", "Pand_Flust.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Cer_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Angry.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jus_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jus_Curious.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Az_Note.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Zd_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_Puzzled.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Idle.png");

		IsLoad = true;
	}
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


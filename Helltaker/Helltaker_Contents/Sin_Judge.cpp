#include "Sin_Judge.h"

Sin_Judge::Sin_Judge()
{
}

Sin_Judge::~Sin_Judge()
{
}

void Sin_Judge::BeginPlay()
{
	Character::BeginPlay();
}

void Sin_Judge::Tick(float _DeltaTime)
{
	Character::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Judge::Intro_AppearStart()
{
	GetImageRenderer()->CreateAnimation(
		"Jud_Intro", 
		"Jud_Intro", 
		{ 0, 1, 2, 3 },	
		{ 0.08f, 0.16f, 0.32f, 0.64f },	
		false);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 1.0f, 0.692f };
	FVector Pos = { 0.0f, (-0.0384f) };
	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Jud_Intro");
	GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });
}

void Sin_Judge::Intro_Appear(float _DeltaTime)
{
	if (1 == GetImageRenderer()->GetCurAnimationFrame())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.558f, 0.692f };
		GetImageRenderer()->SetScale(WinScale * Scale);
	}
}

void Sin_Judge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinJudgeState::Intro_Appear:
		Intro_Appear(_DeltaTime);
		break;
	}
}

void Sin_Judge::StateChange(ESinJudgeState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinJudgeState::Intro_Appear:
			Intro_AppearStart();
			break;
		}
	}

	State = _State;
}
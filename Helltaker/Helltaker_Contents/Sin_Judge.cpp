#include "Sin_Judge.h"

#include "SinCutSceneManager.h"
#include "Sin_Dialogue.h"

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
	GetImageRenderer()->CreateAnimation("Jud_Intro", "Jud_Intro", { 0, 1, 2, 3 }, { 0.08f, 0.08f, 0.32f, 0.0f }, false);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 1.0f, 0.692f };
	FVector Pos = { 0.0f, (-0.0402f) };
	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Jud_Intro");
	GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });

	OrderCount = 0;
}

void Sin_Judge::Intro_Appear()
{
	switch (OrderCount)
	{
	case 0:
		Intro_Appear1();
		break;
	case 1:
		Intro_Appear2();
		break;
	}
}

void Sin_Judge::Intro_Appear1()
{
	++OrderCount;
}

void Sin_Judge::Intro_Appear2()
{
	if (1 == GetImageRenderer()->GetCurAnimationFrame())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.558f, 0.692f };
		GetImageRenderer()->SetScale(WinScale * Scale);
		GetSinCutSceneChapter()->C_StateChange(ESinSceneState::End);
	}

	if (3 == GetImageRenderer()->GetCurAnimationFrame())
	{
		GetSinCutSceneChapter()->C_StateChange(ESinSceneState::End);
	}

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		StateChange(ESinJudgeState::None);
	}
}

void Sin_Judge::Chap3_FlyStart()
{
	GetImageRenderer()->CreateAnimation("Jud_Pose", "Jud_Pose", 0, 2, 0.02f, false);
	GetImageRenderer()->CreateAnimation("Jud_Fly", "Jud_Fly", 0, 4, 0.01f, false);

	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Jud_Pose");
	OrderCount = 0;
}

void Sin_Judge::Chap3_Fly()
{
	switch (OrderCount)
	{
	case 0:
		Chap3_Fly1();
		break;
	}
}

void Sin_Judge::Chap3_Fly1()
{
	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.265f, 0.626f};
		FVector Pos = { 0.0f, -0.05f };
		GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });
		GetImageRenderer()->AnimationReset();
		GetImageRenderer()->ChangeAnimation("Jud_Fly");
		GetSinCutSceneChapter()->C_GetDialogue()->StateChange(ESinDialogueState::Move);
		++OrderCount;
	}
}

void Sin_Judge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinJudgeState::Intro_Appear:
		Intro_Appear();
		break;
	case ESinJudgeState::Chap3_Fly:
		Chap3_Fly();
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
		case ESinJudgeState::Chap3_Fly:
			Chap3_FlyStart();
			break;
		}
	}

	State = _State;
}
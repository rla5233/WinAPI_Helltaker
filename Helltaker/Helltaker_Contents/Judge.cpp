#include "Judge.h"

bool Judge::IsLoad = false;

Judge::Judge()
{
}

Judge::~Judge()
{
}

void Judge::BeginPlay()
{
	Character::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Scene\\Characters\\Jud_Arm", "L_Arm");
		ContentsHelper::LoadFolder("Scene\\Characters\\Jud_Arm", "R_Arm");
		
		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Intro");

		IsLoad = true;
	}
}

void Judge::Tick(float _DeltaTime)
{
	Character::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Judge::Intro_AppearStart()
{
}

void Judge::Intro_Appear(float _DeltaTime)
{
}

void Judge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinJudgeState::Intro_Appear:
		Intro_Appear(_DeltaTime);
		break;
	}
}

void Judge::StateChange(ESinJudgeState _State)
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
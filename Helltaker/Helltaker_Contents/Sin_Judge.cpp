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
}

void Sin_Judge::Intro_Appear(float _DeltaTime)
{
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
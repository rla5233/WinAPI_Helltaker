#include "SinCutSceneManager.h"

bool SinCutSceneManager::IsLoad = false;

SinCutSceneManager::SinCutSceneManager()
{
}

SinCutSceneManager::~SinCutSceneManager()
{
}

void SinCutSceneManager::BeginPlay()
{
	SinChapterManager::BeginPlay();

	if (false == IsLoad)
	{


		IsLoad = true;
	}
}

void SinCutSceneManager::Tick(float _DeltaTime)
{
	SinChapterManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void SinCutSceneManager::EnterStart()
{
}

void SinCutSceneManager::Enter(float _DeltaTime)
{
}

void SinCutSceneManager::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinSceneState::Enter:
		Enter(_DeltaTime);
		break;
	default:
		break;
	}
}

void SinCutSceneManager::C_StateChange(ESinSceneState _State)
{
	if (State != _State)
	{	
		switch (_State)
		{
		case ESinSceneState::Enter:
			EnterStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}
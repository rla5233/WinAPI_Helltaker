#include "SinOpening.h"

#include "Character.h"
#include "Scene.h"
#include "UI.h"

#include <EnginePlatform/EngineSound.h>

bool SinOpening::IsLoad = false;
const std::vector<const char*> SinOpening::SinOpening_Script =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "고위 기소관 저지먼트",
	/* 2  Script 1  */ "마치 천 번은 죽은 것 같은 느낌이다. 하지만 불길은\n사그라들고... 어찌됐든 당신은 아직 살아있는 것 같다.",
	/* 3  Script 2  */ "칩입자 녀석, 이제야 찾았다!\n넌 아직 죽을 수 없어.",
	/* 4  Script 3  */ "나와 함께 오랜 시간을 보내야 할 거다.",
	/* 5  Script 4  */ "죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!"
};

SinOpening::SinOpening()
{
}

SinOpening::~SinOpening()
{

}

void SinOpening::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{



		IsLoad = false;
	}
}

void SinOpening::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");

	M_StateChange(ESinState::CutScene);
}

void SinOpening::CutSceneStart()
{
	SinChapterManager::CutSceneStart();

	C_SpawnBooper();
	C_BooperTextSet(SinOpening_Script[2]);
	C_BooperSetTextPosition(2);
}

void SinOpening::EnterStart()
{

}

void SinOpening::Enter(float _DeltaTime)
{

}



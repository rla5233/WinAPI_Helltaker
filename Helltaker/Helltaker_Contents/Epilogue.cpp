#include "Epilogue.h"

#include "Scene.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const std::vector<const char*> Epilogue::Epilogue_Script =
{
	/* 0  Script 1 */ "그리하여 당신의 여정은 끝이 났다.",


};

Epilogue::Epilogue()
{
}

Epilogue::~Epilogue()
{
}

void Epilogue::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{

		AddChapterSet("Epilogue");

		IsLoad = true;
	}
}

void Epilogue::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	C_SpawnBooper();

	C_BooperTextSet(Epilogue_Script[0]);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	UEngineSound::SoundPlay("transition_off.wav");


}


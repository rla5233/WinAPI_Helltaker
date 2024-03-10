#include "Epilogue.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;
const std::vector<const char*> Epilogue::Epilogue_Script;

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
		ContentsHelper::LoadImg("BackGround", "ChapterBG_Epilogue.png");



		AddChapterSet("Epilogue");
		IsLoad = true;
	}
}

void Epilogue::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, false , false , true, true, false, false, false, false , false , false, false  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.11f, 0.16f });

	CreateBG("ChapterBG_Epilogue");

	M_SpawnEpilHero({ 14, 1 });






	M_StateChange(EChapterState::Idle);
	GetChapterBGM().Off();

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Epilogue::Tick(float _DeltaTime)
{
	HellTakerManager::Tick(_DeltaTime);
}

void Epilogue::EnterStart()
{

}

void Epilogue::Enter()
{

}

void Epilogue::Enter1()
{

}

void Epilogue::EnterCutScene()
{
	
}

void Epilogue::IdleStart()
{
}

void Epilogue::Idle(float _DeltaTime)
{
}

void Epilogue::StateUpdate(float _DeltaTime)
{

}

void Epilogue::StateChange(EEpilogueState _State)
{

}


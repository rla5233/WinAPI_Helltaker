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

		ContentsHelper::LoadFolder("Chapter\\Demon", "Lucy_Epil");

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
		{ true, true, true, true, true , true , true, true, true, true, false, true , true , true, true  },
		{ false, true, false, false, false , true , true, true, true, true, false, false , true , false, false  },
		{ false, true, false, false, false , true , true, true, true, true, false, false , true , false, false  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  },
		{ true, true, true, true, true , true , true, true, true, true, true, true , true , true, true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.11f, 0.16f });

	CreateBG("ChapterBG_Epilogue");

	M_SpawnEpilHero({ 14, 1 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	
	FVector Scale = { 0.049f, 0.08f };
	FVector Pos = { -0.002f, -0.007f };
	M_SpawnDemon({ 1, 0 }, "Azazel", { WinScale * Pos, WinScale * Scale });

	Scale = { 0.047f, 0.08f };
	Pos = { 0.0f, -0.008f };
	M_SpawnDemon({ 5, 0 }, "Zdrada", { WinScale * Pos, WinScale * Scale });

	Scale = { 0.047f, 0.08f };	
	Pos = { 0.0f, -0.009f };
	M_SpawnDemon({ 10, 3 }, "Justice", { WinScale * Pos, WinScale * Scale });

	Scale = { 0.052f, 0.093f };
	Pos = { 0.0f, -0.013f };
	M_SpawnDemon({ 11, 3 }, "Lucy_Epil", { WinScale * Pos, WinScale * Scale });


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

void Epilogue::CutSceneCheck()
{

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


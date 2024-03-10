#include "Epilogue.h"

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

		IsLoad = true;
	}
}

void Epilogue::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);
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
	AllCutSceneActorOff();
	TransitionOn();

	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, true , true , false },
		{ false, true , true , true , true , true , false },
		{ false, true , true , true , true , false, false },
		{ true , true , false, false, false, false, false },
		{ true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.32f, 0.208f });

	CreateBG("ChapterBG_001");
	M_SpawnHero({ 5, 0 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.049f, WinScale.Y * 0.08f };
	FVector Pos = { WinScale.X * (-0.003f), WinScale.Y * (-0.01f) };
	M_SpawnDemon({ 6, 5 }, "PandeMonica", { Pos, Scale });
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


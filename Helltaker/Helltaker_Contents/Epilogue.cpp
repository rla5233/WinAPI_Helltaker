#include "Epilogue.h"

#include "Character.h"
#include "Demon.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;
const std::vector<const char*> Epilogue::Epilogue_Script =
{
	/* 0 Demon	  */ "지옥의 CEO 루시퍼",
	/* 1 Script 1 */ "팬케이크 한 판 더 완성이다.",
	/* 2 Script 2 */ "그리고 차아아암 맛있어...",
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
		ContentsHelper::LoadImg("BackGround", "ChapterBG_Epilogue.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Home.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_PanCake.png");

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
		{ false, false, false, false, false, false, true, true , false, false, false, false, false, false, false },
		{ true , true , true , true , true , true , true, true , true , true , false, true , true , true , true  },
		{ false, true , false, false, false, true , true, true , true , true , false, false, true , false, false },
		{ false, true , false, false, false, true , true, true , true , true , false, false, true , false, false },
		{ false, true , true , false, false, false, true, true , true , true , true , true , true , true , false },
		{ false, true , true , true , false, false, true, true , false, false, false, false, true , true , false },
		{ false, false, false, false, false, false, true, false, false, false, false, false, true , true , false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.11f, 0.16f });

	CreateBG("ChapterBG_Epilogue");

	M_SpawnEpilHero({ 14, 1 });

	FVector WinScale = ContentsHelper::GetWindowScale();
	
	FVector Scale = { 0.049f, 0.08f };
	FVector Pos = { -0.002f, -0.007f };
	M_SpawnDemon({ 1, 0 }, "Azazel", { WinScale * Pos, WinScale * Scale });
	M_SpawnDemon({ 7, 6 }, "PandeMonica", { WinScale * Pos, WinScale * Scale });


	Scale = { 0.047f, 0.08f };
	Pos = { 0.0f, -0.008f };
	M_SpawnDemon({ 5, 0 }, "Zdrada", { WinScale * Pos, WinScale * Scale });

	M_SpawnDemon({ 0, 3 }, "Cerberus", { WinScale * Pos, WinScale * Scale });
	M_SpawnDemon({ 0, 4 }, "Cerberus", { WinScale * Pos, WinScale * Scale });
	M_SpawnDemon({ 0, 5 }, "Cerberus", { WinScale * Pos, WinScale * Scale });

	M_SpawnDemon({ 10, 3 }, "Justice", { WinScale * Pos, WinScale * Scale });

	M_SpawnDemon({ 5, 4 }, "Malina", { WinScale * Pos, WinScale * Scale });

	Scale = { 0.052f, 0.093f };
	Pos = { 0.0f, -0.013f };
	M_SpawnDemon({ 11, 3 }, "Lucy_Epil", { WinScale * Pos, WinScale * Scale });

	M_SpawnDemon({ 3, 4 }, "Judge", { WinScale * Pos, WinScale * Scale });

	Scale = { 0.048f, 0.08f };
	Pos = { 0.0f, -0.01f };
	M_SpawnDemon({ 14, 4 }, "Modeus", { WinScale * Pos, WinScale * Scale });

	SpawnPolice();

	M_StateChange(EChapterState::Idle);
	GetChapterBGM().Off();

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Epilogue::M_SpawnDemon(Point _Point, std::string_view _Name, const FTransform& _FTransform)
{
	ChapterManager::M_SpawnDemon(_Point, _Name, _FTransform);
	CanCutScene[UEngineString::ToUpper(_Name.data())] = true;
}

void Epilogue::SpawnPolice()
{
	FVector WinScale = ContentsHelper::GetWindowScale();

	FVector Scale = { 0.049f, 0.08f };
	FVector Pos = { -0.002f, -0.007f };
	ChapterManager::M_SpawnDemon({ 1, 6 }, "Azazel", { WinScale * Pos, WinScale * Scale });
	(*AllChapterDemon.rbegin())->SetName("Police");
	(*AllChapterDemon.rbegin())->GetImageRenderer()->ActiveOff();
	CanCutScene[UEngineString::ToUpper("Police")] = true;
}

void Epilogue::CutSceneCheck()
{
	Point HeroCurPoint = M_GetHeroLocationPoint();
	for (Demon* Demon : AllChapterDemon)	
	{
		Point DemonPoint = Demon->GetLocationPoint();
		if (DemonPoint + Point::Left == HeroCurPoint ||
			DemonPoint + Point::Right == HeroCurPoint ||
			DemonPoint + Point::Up == HeroCurPoint ||
			DemonPoint + Point::Down == HeroCurPoint)
		{
			DemonKeyName = Demon->GetName();

			if (true == CanCutScene[DemonKeyName])
			{
				M_StateChange(EChapterState::CutScene);
				CanCutScene[DemonKeyName] = false;
			}
		}
	}
}

void Epilogue::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Home.png");

	if ("LUCY_EPIL" == DemonKeyName)
	{
		StateChange(EEpilogueState::LucyCutScene);
	}
}

void Epilogue::Enter(float _DeltaTime)
{
}

void Epilogue::EnterStart()
{
	OrderCount = 0;
}

void Epilogue::LucyCutSceneStart()
{
	FVector Scale = { 0.233f, 0.632f };
	FVector Pos = { -0.015f, 0.0f };
	C_SpawnCharacter("Lu", "Lu_PanCake.png", Epilogue_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_SpawnBooper();
	C_BooperTextSet(Epilogue_Script[1]);
}

void Epilogue::LucyCutScene(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		LucyCutScene1();
		break;
	}
}

void Epilogue::LucyCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.233f, 0.632f };
		FVector Pos = { -0.015f, 0.0f };
		

		C_SpawnBooper();
		C_BooperTextSet(Epilogue_Script[2]);

		++OrderCount;
	}
}

void Epilogue::Tick(float _DeltaTime)
{
	HellTakerManager::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Epilogue::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EEpilogueState::LucyCutScene:
		LucyCutScene(_DeltaTime);
		break;
	}
}

void Epilogue::StateChange(EEpilogueState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EEpilogueState::LucyCutScene:
			LucyCutSceneStart();
			break;
		}
	}

	State = _State;
}

#include "Epilogue.h"

#include "Character.h"
#include "Demon.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

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
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Yum.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Man_PanCake_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Man_PanCake_002.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Unsure.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Talk.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Book.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Shy.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jus_PanCake.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jus_Blind.png");
		
		
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
	State = EEpilogueState::None;

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
	ChapterManager::CutSceneStart();	

	C_StateChange(ECutSceneState::None);
	C_StateChange(ECutSceneState::Enter);

	UEngineSound::SoundPlay("dialogue_start.wav");

	if (UEngineString::ToUpper("Lucy_Epil") == DemonKeyName)
	{
		StateChange(EEpilogueState::LucyCutScene);
	}
	else if (UEngineString::ToUpper("Modeus") == DemonKeyName)
	{
		StateChange(EEpilogueState::ModCutScene);
	}
	else if (UEngineString::ToUpper("Justice") == DemonKeyName)
	{
		StateChange(EEpilogueState::JusCutScene);
	}
}

void Epilogue::GoBackChapter()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		StateChange(EEpilogueState::None);

		AllCutSceneActorOff();
		C_StateChange(ECutSceneState::None);
		ReturnToChap(DemonKeyName);
		DemonKeyName = "";
	}
}

void Epilogue::Enter(float _DeltaTime)
{
	ResetCheck();
}

void Epilogue::EnterStart()
{
	OrderCount = 0;
}

void Epilogue::LucyCutSceneStart()
{
	C_CreateSceneBG();
	C_SpawnDialogue("DialogueBG_Home.png");
	
	FVector Scale = { 0.233f, 0.632f };
	FVector Pos = { -0.015f, 0.0f };
	C_SpawnCharacter("Lu", "Lu_PanCake.png", Lucy_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_SpawnBooper();
	C_BooperTextSet(Lucy_Script[1]);
}

void Epilogue::LucyCutScene()
{
	switch (OrderCount)
	{
	case 0:
		LucyCutScene1();
		break;
	case 1:
		LucyCutScene2();
		break;
	case 2:
		LucyCutScene3();
		break;
	case 3:
		LucyCutScene4();
		break;
	case 4:
		LucyCutScene5();
		break;
	case 5:
		LucyCutScene6();
		break;
	case 6:
		LucyCutScene7();
		break;
	case 7:
		GoBackChapter();
		break;
	}
}

void Epilogue::LucyCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.247f, 0.626f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Lu_Yum.png", { WinScale * Pos , WinScale * Scale });

		C_BooperTextSet(Lucy_Script[2]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Lucy_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Lucy_Script[8]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.258f, 0.642f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Lu_Unsure.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Lucy_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Lucy_Script[3]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Lucy_Script[4]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Lucy_Script[5]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Lucy_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Lucy_Script[9]);

		++OrderCount;
	}	
}

void Epilogue::LucyCutScene7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.277f, 0.644f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Lu_Talk.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Lucy_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Lucy_Script[6]);

		++OrderCount;
	}
}

void Epilogue::ModCutSceneStart()
{
	AllCutSceneActorOn();
	
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 0.391f, 0.674f };
	FVector Pos = { 0.0f, 0.0f };
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[5]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);
	
	C_BooperTextSet(Mod_Script[6]);
}

void Epilogue::ModCutScene()
{
	switch (OrderCount)
	{
	case 0:
		ModCutScene1();
		break;
	case 1:
		ModCutScene2();
		break;
	case 2:
		ModCutScene3();
		break;
	case 3:
		ModCutScene4();
		break;
	case 4:
		ModCutScene5();
		break;
	case 5:
		ModCutScene6();
		break;
	case 6:
		GoBackChapter();
		break;
	}
}

void Epilogue::ModCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.226f, 0.588f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mod_Book.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[1]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[5]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[7]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.226f, 0.588f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mod_Book.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[2]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Mod_Script[3]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[5]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[8]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.215f, 0.693f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mod_Shy.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[4]);

		++OrderCount;
	}
}

void Epilogue::JusCutSceneStart()
{
	AllCutSceneActorOn();

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 0.391f, 0.674f };
	FVector Pos = { 0.0f, 0.0f };
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[7]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Jus_Script[8]);
}

void Epilogue::JusCutScene()
{
	switch (OrderCount)
	{
	case 0:
		JusCutScene1();
		break;
	case 1:
		JusCutScene2();
		break;
	case 2:
		JusCutScene3();
		break;
	case 3:
		JusCutScene4();
		break;
	case 4:
		JusCutScene5();
		break;
	case 5:
		JusCutScene6();
		break;
	case 6:
		JusCutScene7();
		break;
	case 7:
		JusCutScene8();
		break;
	case 8:
		JusCutScene9();
		break;
	case 9:
		GoBackChapter();
		break;
	}
}

void Epilogue::JusCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[1]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[9]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[2]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[10]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.558f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_Blind.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[3]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.22f, 0.612f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_Idle.png", { WinScale * Pos , WinScale * Scale });

		C_BooperTextSet(Jus_Script[4]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.391f, 0.674f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Man_PanCake_002.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[11]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene8()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.228f, 0.567f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_Curious.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[5]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene9()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		
		C_BooperTextSet(Jus_Script[6]);

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
		LucyCutScene();
		break;
	case EEpilogueState::ModCutScene:
		ModCutScene();
		break;
	case EEpilogueState::JusCutScene:
		JusCutScene();
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
		case EEpilogueState::ModCutScene:
			ModCutSceneStart();
			break;
		case EEpilogueState::JusCutScene:
			JusCutSceneStart();
			break;
		}
	}

	State = _State;
}

const std::vector<const char*> Epilogue::Lucy_Script =
{
	/* 0 Demon	  */ "지옥의 CEO 루시퍼",
	/* 1 Script 1 */ "팬케이크 한 판 더 완성이다.",
	/* 2 Script 2 */ "그리고 차아아암 맛있어...",
	/* 3 Script 3 */ "새삼스럽게. 별 것도 아니었어.",
	/* 4 Script 4 */ "그나저나 참, 네가 어떻게 매번 얇게 구워내는지 아직도\n모르겠어.",
	/* 5 Script 5 */ "어떻게 팬케이크를 그렇게 공중으로 올려 뒤집는지도\n궁금하고. 무슨 마법이라도 쓰는 것 같아.",
	/* 6 Script 6 */ "아 그러시겠어. 애들한테 팬케이크나 나눠줘.",

	/* 7 Man	  */ "헬테이커",
	/* 8 Script 1 */ "도와줘서 고마워",
	/* 9 Script 2 */ "경험이지"
};
const std::vector<const char*> Epilogue::Mod_Script =
{
	/* 0 Demon	  */ "음란한 악마 모데우스",
	/* 1 Script 1 */ "...",
	/* 2 Script 2 */ "로맨스라는걸 듣도 보도 못했어. 여지껏 본 것 중에 제일\n변태적이야.",
	/* 3 Script 3 */ "어쩌면 내가 잘못 살아온 게 아닐까?",
	/* 4 Script 4 */ "이런 이상성욕 변태일 줄 알았어.",

	/* 5 Man	  */ "헬테이커",
	/* 6 Script 1 */ "자 팬케이크.",
	/* 7 Script 2 */ "로맨틱 코미디를 읽어?",
	/* 8 Script 3 */ "뭐, 데이트라도 갈까?"
};

const std::vector<const char*> Epilogue::Jus_Script
{
	/* 0  Demon	   */ "끝내주는 악마 저스티스",
	/* 1  Script 1 */ "끝내주네. 근데 궁금한 게 있는데 말야.",
	/* 2  Script 2 */ "애들 말로는 네가 선글라스를 절대 안 벗는다던데. 왜 그래?",
	/* 3  Script 3 */ "아, 나 말이야? 왜냐면 눈이 멀었거든.",
	/* 4  Script 4 */ "내 얘기는 그럼 됐고. 너는?",
	/* 5  Script 5 */ "에이. 애들이랑 내기까지 했는데.",
	/* 6  Script 6 */ "네가 눈에서 레이저 못 쏘면 내 10달러를 잃는다고.",

	/* 7  Man	   */ "헬테이커",
	/* 8  Script 1 */ "자 팬케이크.",
	/* 9  Script 2 */ "말해 봐.",
	/* 10 Script 3 */ "나도 너한테 똑같이 묻고 싶은데.",
	/* 11 Script 4 */ "언젠가 다음에..."
};

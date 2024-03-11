#include "Epilogue.h"

#include "Character.h"
#include "Demon.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const FVector Epilogue::ManScale = { 0.391f, 0.674f };
const FVector Epilogue::ManPos = { 0.0f, 0.0f };

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
		ContentsHelper::LoadImg("Scene\\Characters", "Pand_Cup.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Pand_Drink.png");
		ContentsHelper::LoadImg("Scene\\Characters", "PandS_Cup.png");
		ContentsHelper::LoadImg("Scene\\Characters", "PandS_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_Phone.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_Bottle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_PreBottle.png");
		
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
	else if (UEngineString::ToUpper("PandeMonica") == DemonKeyName)
	{
		StateChange(EEpilogueState::PandCutScene);
	}
	else if (UEngineString::ToUpper("Malina") == DemonKeyName)
	{
		StateChange(EEpilogueState::MalCutScene);
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
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
		C_ChangeCharactrer("Man_PanCake_002.png", { WinScale * ManPos , WinScale * ManScale });
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

void Epilogue::PandCutSceneStart()
{
	AllCutSceneActorOn();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[8]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Pand_Script[9]);
}

void Epilogue::PandCutScene()
{
	switch (OrderCount)
	{
	case 0:
		PandCutScene1();
		break;
	case 1:
		PandCutScene2();
		break;
	case 2:
		PandCutScene3();
		break;
	case 3:
		PandCutScene4();
		break;
	case 4:
		PandCutScene5();
		break;
	case 5:
		PandCutScene6();
		break;
	case 6:
		PandCutScene7();
		break;
	case 7:
		PandCutScene8();
		break;
	case 8:
		PandCutScene9();
		break;
	case 9:
		PandCutScene10();
		break;
	case 10:
		GoBackChapter();
		break;
	}
}

void Epilogue::PandCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.222f, 0.518f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Pand_Cup.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[2]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.607f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Pand_Drink.png", { WinScale * Pos , WinScale * Scale });

		C_BooperTextSet(Pand_Script[2]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.218f, 0.597f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("PandS_Idle.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);

		C_BooperTextSet(Pand_Script[3]);
			
		++OrderCount;
	}
}

void Epilogue::PandCutScene4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[8]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[10]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.222f, 0.573f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("PandS_Cup.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[4]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Pand_Script[5]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_002.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[8]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[11]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene8()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.218f, 0.597f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("PandS_Idle.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[6]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene9()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_002.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[8]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[12]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene10()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.607f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Pand_Drink.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[7]);

		++OrderCount;
	}
}

void Epilogue::MalCutSceneStart()
{
	AllCutSceneActorOn();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[5]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Mal_Script[6]);
}

void Epilogue::MalCutScene()
{
	switch (OrderCount)
	{
	case 0:
		MalCutScene1();
		break;
	case 1:
		MalCutScene2();
		break;
	case 2:
		MalCutScene3();
		break;
	case 3:
		MalCutScene4();
		break;
	case 4:
		MalCutScene5();
		break;
	case 5:
		GoBackChapter();
		break;
	}
}

void Epilogue::MalCutScene1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.193f, 0.551f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mal_Phone.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mal_Script[1]);	

		++OrderCount;
	}
}

void Epilogue::MalCutScene2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Mal_Script[2]);

		++OrderCount;
	}
}

void Epilogue::MalCutScene3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[5]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mal_Script[7]);

		++OrderCount;
	}
}

void Epilogue::MalCutScene4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.1875f, 0.481f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mal_PreBottle.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mal_Script[3]);

		++OrderCount;
	}
}

void Epilogue::MalCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.2292f, 0.481f };
		FVector Pos = { 0.0f, 0.0f };
		C_ChangeCharactrer("Mal_Bottle.png", { WinScale * Pos , WinScale * Scale });

		C_BooperTextSet(Mal_Script[4]);

		++OrderCount;
	}
}

void Epilogue::ZdCutSceneStart()
{
	AllCutSceneActorOn();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[4]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Zd_Script[5]);
}

void Epilogue::ZdCutScene()
{
	switch (OrderCount)
	{
	case 0:
		ZdCutScene1();
		break;
	case 1:
		ZdCutScene2();
		break;
	case 2:
		ZdCutScene3();
		break;
	case 3:
		ZdCutScene4();
		break;
	case 4:
		ZdCutScene5();
		break;
	}
}

void Epilogue::ZdCutScene1()
{}

void Epilogue::ZdCutScene2()
{}

void Epilogue::ZdCutScene3()
{}

void Epilogue::ZdCutScene4()
{}

void Epilogue::ZdCutScene5()
{}

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
	case EEpilogueState::PandCutScene:
		PandCutScene();
		break;
	case EEpilogueState::MalCutScene:
		MalCutScene();
		break;
	case EEpilogueState::ZdCutScene:
		ZdCutScene();
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
		case EEpilogueState::PandCutScene:
			PandCutSceneStart();
			break;
		case EEpilogueState::MalCutScene:
			MalCutSceneStart();
			break;
		case EEpilogueState::ZdCutScene:
			ZdCutSceneStart();
			break;
		}
	}

	State = _State;
}

const std::vector<const char*> Epilogue::Lucy_Script =
{
	/* 0 Demon	  */ "������ CEO �����",
	/* 1 Script 1 */ "������ũ �� �� �� �ϼ��̴�.",
	/* 2 Script 2 */ "�׸��� ���ƾƾ� ���־�...",
	/* 3 Script 3 */ "���ｺ����. �� �͵� �ƴϾ���.",
	/* 4 Script 4 */ "�׳����� ��, �װ� ��� �Ź� ��� ���������� ������\n�𸣰ھ�.",
	/* 5 Script 5 */ "��� ������ũ�� �׷��� �������� �÷� ����������\n�ñ��ϰ�. ���� �����̶� ���� �� ����.",
	/* 6 Script 6 */ "�� �׷��ðھ�. �ֵ����� ������ũ�� ������.",

	/* 7 Man	  */ "������Ŀ",
	/* 8 Script 1 */ "�����༭ ����",
	/* 9 Script 2 */ "��������"
};
const std::vector<const char*> Epilogue::Mod_Script =
{
	/* 0 Demon	  */ "������ �Ǹ� �𵥿콺",
	/* 1 Script 1 */ "...",
	/* 2 Script 2 */ "�θǽ���°� �赵 ���� ���߾�. ������ �� �� �߿� ����\n�������̾�.",
	/* 3 Script 3 */ "��¼�� ���� �߸� ��ƿ� �� �ƴұ�?",
	/* 4 Script 4 */ "�̷� �̻󼺿� ������ �� �˾Ҿ�.",

	/* 5 Man	  */ "������Ŀ",
	/* 6 Script 1 */ "�� ������ũ.",
	/* 7 Script 2 */ "�θ�ƽ �ڹ̵� �о�?",
	/* 8 Script 3 */ "��, ����Ʈ�� ����?"
};
const std::vector<const char*> Epilogue::Jus_Script
{
	/* 0  Demon	   */ "�����ִ� �Ǹ� ����Ƽ��",
	/* 1  Script 1 */ "�����ֳ�. �ٵ� �ñ��� �� �ִµ� ����.",
	/* 2  Script 2 */ "�ֵ� ���δ� �װ� ���۶󽺸� ���� �� ���´ٴ���. �� �׷�?",
	/* 3  Script 3 */ "��, �� ���̾�? �ֳĸ� ���� �־��ŵ�.",
	/* 4  Script 4 */ "�� ���� �׷� �ư�. �ʴ�?",
	/* 5  Script 5 */ "����. �ֵ��̶� ������� �ߴµ�.",
	/* 6  Script 6 */ "�װ� ������ ������ �� ��� �� 10�޷��� �Ҵ´ٰ�.",

	/* 7  Man	   */ "������Ŀ",
	/* 8  Script 1 */ "�� ������ũ.",
	/* 9  Script 2 */ "���� ��.",
	/* 10 Script 3 */ "���� ������ �Ȱ��� ���� ������.",
	/* 11 Script 4 */ "������ ������..."
};
const std::vector<const char*> Epilogue::Pand_Script =
{
	/* 0  Demon	   */ "�ǰ��� �Ǹ� �ǵ����ī",
	/* 1  Demon	   */ "�������� �Ǹ� �ǵ����ī",
	/* 2  Script 1 */ "...",
	/* 3  Script 2 */ "��! ���� �ǰ��� �Ǹ��� ������.",
	/* 4  Script 3 */ "�ƴ�... �� ������. �̹��� ������ �� �߰�.",
	/* 5  Script 4 */ "�̴�θ� �Ѵٸ� �հ��� ������ ������ ��� �ְڳ�.",
	/* 6  Script 5 */ "�׷����� ��ġ�� ������ ������� ��. ���� ������ �� ���� ��\n������.",
	/* 7  Script 6 */ "����� �װ� �ϰ� �־����.",

	/* 8  Man	   */ "������Ŀ",
	/* 9  Script 1 */ "�� ������ũ�� Ŀ��.",
	/* 10 Script 2 */ "�� �ʹ� ���ϰ� �̾ҳ�?",
	/* 11 Script 3 */ "�׷�...",
	/* 12 Script 4 */ "���� �� ���� 5�� 15�п� ���� ���������� ����?"
};
const std::vector<const char*> Epilogue::Mal_Script =
{
	/* 0 Demon	  */ "��ū���� �Ǹ� ������",
	/* 1 Script 1 */ "�� ���� ���� ���� ���� ã�Ⱑ �� �̷��� �����?",
	/* 2 Script 2 */ "���� ������ �͵��� �˴� ���� �� �ļ����̳� ǥ����\n�����̾�.",
	/* 3 Script 3 */ "�� �������Ե�, ���� �׷��� ��.",
	/* 4 Script 4 */ "���� �� �ʿ��ϰ�����.",

	/* 5 Man	  */ "������Ŀ",
	/* 6 Script 1 */ "�� ������ũ.",
	/* 7 Script 2 */ "�׷��� �� �� �� ������.",
};
const std::vector<const char*> Epilogue::Zd_Script =
{
	/* 0 Demon	  */ "�󽺷��� �Ǹ� �����",
	/* 1 Script 1 */ "����. �ٵ� �� �� ������ �ϴµ�.",
	/* 2 Script 2 */ "�׷���? ���̶� �ַ���? �� ��, �� ���� ���� �����ε�.",
	/* 3 Script 3 */ "Ȯ ����.",

	/* 4 Man	  */ "������Ŀ",
	/* 5 Script 1 */ "�� ������ũ.",
	/* 6 Script 2 */ "�ǳ����� �ݿ��̾�.",
	/* 7 Script 3 */ "���� ���� �� �ƴϾ�?",
};
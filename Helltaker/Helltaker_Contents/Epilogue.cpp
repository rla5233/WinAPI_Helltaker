#include "Epilogue.h"

#include "Character.h"
#include "Scene.h"
#include "Demon.h"
#include "Hero.h"

#include <EnginePlatform/EngineSound.h>

bool Epilogue::IsLoad = false;

const FVector Epilogue::ManScale = { 0.391f, 0.674f };
const FVector Epilogue::ManPos = { 0.0f, -0.032f };

UEngineSoundPlayer Epilogue::EpilBGMPlayer;

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
		ContentsHelper::LoadImg("BackGround", "EndingBG.png");
		ContentsHelper::LoadImg("Chapter\\Component", "PoliceCar.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Home.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_Ending.png");
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
		ContentsHelper::LoadImg("Scene\\Characters", "Zd_Snap.png");
		ContentsHelper::LoadImg("Scene\\Characters\\Zd_Ignite", "Zd_Ignite_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Az_Shock.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Cer_Bad.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_PanCake.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Police_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Police_002.png");
		
		ContentsHelper::LoadFolder("Chapter\\Demon", "Lucy_Epil");
		ContentsHelper::LoadFolder("Scene\\Characters", "Zd_Ignite");


		ContentsHelper::LoadSound("Sound\\BGM", "Luminescent.wav");

		EpilBGMPlayer = UEngineSound::SoundPlay("Luminescent.wav");
		EpilBGMPlayer.SetVolume(0.8f);
		EpilBGMPlayer.Loop();

		AddChapterSet("Epilogue");
		IsLoad = true;
	}
}

void Epilogue::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	std::vector<std::vector<bool>> Map =
	{// 수정
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

void Epilogue::LevelEnd(ULevel* _NextLevel)
{
	HellTakerManager::LevelEnd(_NextLevel);

	CanCutScene.clear();
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

	Pos = { 0.135f, 0.873f };
	Scale = { 0.14f, 0.148f };
	RenderActor* PoliceCar = SpawnActor<RenderActor>(RenderOrder::RenderActor);
	PoliceCar->SetName("PoliceCar");
	PoliceCar->SetActorLocation(WinScale * Pos);
	UImageRenderer* Pol_CarImgRenderer = PoliceCar->CreateImageRenderer(RenderOrder::RenderActor);
	Pol_CarImgRenderer->SetImage("PoliceCar.png");
	Pol_CarImgRenderer->SetScale({ WinScale * Scale });
	M_AddActorMap(PoliceCar);
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

				if (UEngineString::ToUpper("Police") != DemonKeyName)
				{
					CanCutScene[DemonKeyName] = false;
				}
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
	else if (UEngineString::ToUpper("Zdrada") == DemonKeyName)
	{
		StateChange(EEpilogueState::ZdCutScene);
	}
	else if (UEngineString::ToUpper("Azazel") == DemonKeyName)
	{
		StateChange(EEpilogueState::AzCutScene);
	}
	else if (UEngineString::ToUpper("Cerberus") == DemonKeyName)
	{
		StateChange(EEpilogueState::CerCutScene);
	}
	else if (UEngineString::ToUpper("Judge") == DemonKeyName)
	{
		StateChange(EEpilogueState::JudCutScene);
	}
	else if (UEngineString::ToUpper("Police") == DemonKeyName)
	{
		StateChange(EEpilogueState::PolCutScene);
	}
}

void Epilogue::GoBackChapter()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
 		StateChange(EEpilogueState::None);

		AllCutSceneActorOff();
		C_StateChange(ECutSceneState::None);

		if (UEngineString::ToUpper("Police") == DemonKeyName)
		{
			DemonKeyName = "";
		}

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
	FVector Pos = { -0.015f, -0.01f };
	C_SpawnCharacter("Lu", "Lu_PanCake.png", Lucy_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_SpawnBooper();
	C_BooperTextSet(Lucy_Script[1]);

	C_SpawnMenubar();
	C_MenubarRenderActiveOff();
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.247f, 0.626f };
		FVector Pos = { 0.022f, -0.008f };
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.258f, 0.642f };
		FVector Pos = { 0.0177f, -0.007f };
		C_ChangeCharactrer("Lu_Unsure.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Lucy_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Lucy_Script[3]);

		++OrderCount;
	}
}

void Epilogue::LucyCutScene4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.277f, 0.644f };
		FVector Pos = { -0.001f, -0.014f };
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
	C_MenubarRenderActiveOff();

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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.226f, 0.588f };
		FVector Pos = { 0.012f, 0.01f };
  		C_ChangeCharactrer("Mod_Book.png", { WinScale * Pos, WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[1]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.226f, 0.588f };
		FVector Pos = { 0.012f, 0.01f };
		C_ChangeCharactrer("Mod_Book.png", { WinScale * Pos, WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mod_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mod_Script[2]);

		++OrderCount;
	}
}

void Epilogue::ModCutScene4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.215f, 0.693f };
		FVector Pos = { -0.01f, -0.038f };
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
	C_MenubarRenderActiveOff();

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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.008f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[1]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.008f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[2]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.558f };
		FVector Pos = { 0.026f, 0.022f };
		C_ChangeCharactrer("Jus_Blind.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[3]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene6()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.228f, 0.567f };
		FVector Pos = { -0.005f, 0.02f };
		C_ChangeCharactrer("Jus_Curious.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jus_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jus_Script[5]);

		++OrderCount;
	}
}

void Epilogue::JusCutScene9()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.291f, 0.59f };
		FVector Pos = { 0.0f, 0.008f };
		C_ChangeCharactrer("Jus_PanCake.png", { WinScale * Pos , WinScale * Scale });
		
		C_BooperTextSet(Jus_Script[6]);

		++OrderCount;
	}
}

void Epilogue::PandCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.222f, 0.555f };
		FVector Pos = { -0.001f, 0.028f };
		C_ChangeCharactrer("Pand_Cup.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[2]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.607f };
		FVector Pos = { 0.008f, 0.002f };
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
		FVector Pos = { -0.006f, 0.008f };
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.222f, 0.573f };
		FVector Pos = { -0.002f, 0.024f };
		C_ChangeCharactrer("PandS_Cup.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[4]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene6()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.218f, 0.597f };
		FVector Pos = { -0.006f, 0.008f };
		C_ChangeCharactrer("PandS_Idle.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pand_Script[1]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pand_Script[6]);

		++OrderCount;
	}
}

void Epilogue::PandCutScene9()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.223f, 0.607f };
		FVector Pos = { 0.008f, 0.002f };
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
	C_MenubarRenderActiveOff();

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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.193f, 0.551f };
		FVector Pos = { 0.002f, 0.028f };
		C_ChangeCharactrer("Mal_Phone.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mal_Script[1]);	

		++OrderCount;
	}
}

void Epilogue::MalCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
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
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.1875f, 0.481f };
		FVector Pos = { -0.001f, 0.064f };
		C_ChangeCharactrer("Mal_PreBottle.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Mal_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Mal_Script[3]);

		++OrderCount;
	}
}

void Epilogue::MalCutScene5()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.2292f, 0.481f };
		FVector Pos = { -0.001f, 0.064f };
		C_ChangeCharactrer("Mal_Bottle.png", { WinScale * Pos , WinScale * Scale });

		C_BooperTextSet(Mal_Script[4]);

		++OrderCount;
	}
}

void Epilogue::ZdCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[4]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Zd_Script[5]);
}

void Epilogue::ZdCutScene(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		ZdCutScene1();
		break;
	case 1:
		ZdCutScene2(_DeltaTime);
		break;
	case 2:
		ZdCutScene3();
		break;
	case 3:
		ZdCutScene4(_DeltaTime);
		break;
	case 4:
		ZdCutScene5();
		break;
	case 5:
		GoBackChapter();
		break;
	}
}

void Epilogue::ZdCutScene1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.216f, 0.5935f };
		FVector Pos = { 0.0f, 0.005f };
		C_ChangeCharactrer("Zd_Ignite_001.png", { WinScale * Pos , WinScale * Scale });
		C_CreateCharacterAnimation("Zd_Ignite", "Zd_Ignite", 0, 3, 0.06f, false);
		C_CreateCharacterAnimation("Zd_Ignite_Double", "Zd_Ignite", 0, 7, 0.06f, false);
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Zd_Script[1]);

		++OrderCount;
	}
}

void Epilogue::ZdCutScene2(float _DeltaTime)
{
	RepeatZdAnim(_DeltaTime);
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_GetSceneCharacter()->GetImageRenderer()->AnimationReset();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[4]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Zd_Script[6]);

		++OrderCount;
	}
}

void Epilogue::ZdCutScene3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.216f, 0.5935f };
		FVector Pos = { 0.0f, 0.005f };
		C_ChangeCharactrer("Zd_Ignite_001.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Zd_Script[2]);

		++OrderCount;
	}
}

void Epilogue::ZdCutScene4(float _DeltaTime)
{
	RepeatZdAnim(_DeltaTime);
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_GetSceneCharacter()->GetImageRenderer()->AnimationReset();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[4]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Zd_Script[7]);

		++OrderCount;
	}
}

void Epilogue::ZdCutScene5()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.207f, 0.596f };
		FVector Pos = { 0.0f, 0.01f };
		C_ChangeCharactrer("Zd_Snap.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Zd_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Zd_Script[3]);

		++OrderCount;
	}
}

void Epilogue::RepeatZdAnim(float _DeltaTime)
{
	if ((ECharacterState::Appear != C_GetSceneCharacter()->GetState())
		&& (nullptr == C_GetSceneCharacter()->GetImageRenderer()->GetCurAnimation()))
	{
		C_ChangeCharacterAnimation("Zd_Ignite");
		ZdAnimOrder = 1;
		TimeCount = ZdAnimDelay;
		return;
	}

	if ((nullptr != C_GetSceneCharacter()->GetImageRenderer()->GetCurAnimation())
		&& true == C_GetSceneCharacter()->GetImageRenderer()->IsCurAnimationEnd())
	{
		if (0.0f >= TimeCount)
		{
			switch (ZdAnimOrder)
			{
			case 0:
			case 1:
				C_ChangeCharacterAnimation("Zd_Ignite");
				++ZdAnimOrder;
				break;
			case 2:
				C_ChangeCharacterAnimation("Zd_Ignite_Double");
				ZdAnimOrder = 0;
				break;
			}

			TimeCount = ZdAnimDelay;
		}

		TimeCount -= _DeltaTime;
	}
}

void Epilogue::AzCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[7]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Az_Script[8]);
}

void Epilogue::AzCutScene()
{
	switch (OrderCount)
	{
	case 0:
		AzCutScene1();
		break;
	case 1:
		AzCutScene2();
		break;
	case 2:
		AzCutScene3();
		break;
	case 3:
		AzCutScene4();
		break;
	case 4:
		AzCutScene5();
		break;
	case 5:
		AzCutScene6();
		break;
	case 6:
		AzCutScene7();
		break;
	case 7:
		AzCutScene8();
		break;
	case 8:
		AzCutScene9();
		break;
	case 9:
		GoBackChapter();
		break;
	}
}

void Epilogue::AzCutScene1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.158f, 0.609f };
		FVector Pos = { -0.01f, 0.0f };
		C_ChangeCharactrer("Az_Shock.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[1]);
		
		++OrderCount;
	}
}

void Epilogue::AzCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[9]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.158f, 0.609f };
		FVector Pos = { -0.01f, 0.0f };
		C_ChangeCharactrer("Az_Shock.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[2]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		C_BooperTextSet(Az_Script[3]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Az_Script[4]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Az_Script[5]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[10]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene8()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.211f, 0.534f };
		FVector Pos = { -0.0064f, 0.04f };
		C_ChangeCharactrer("Az_Note.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[6]);

		++OrderCount;
	}
}

void Epilogue::AzCutScene9()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Az_Script[7]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Az_Script[11]);

		++OrderCount;
	}
}

void Epilogue::CerCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[3]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Cer_Script[4]);
}

void Epilogue::CerCutScene()
{
	switch (OrderCount)
	{
	case 0:
		CerCutScene1();
		break;
	case 1:
		CerCutScene2();
		break;
	case 2:
		CerCutScene3();
		break;
	case 3:
		CerCutScene4();
		break;
	case 4:
		CerCutScene5();
		break;
	case 5:
		GoBackChapter();
		break;
	}
}

void Epilogue::CerCutScene1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.47f, 0.563f };
		FVector Pos = { 0.0f, 0.024f };
		C_ChangeCharactrer("Cer_Bad.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Cer_Script[1]);

		++OrderCount;
	}
}

void Epilogue::CerCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[3]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Cer_Script[5]);

		++OrderCount;
	}
}

void Epilogue::CerCutScene3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.47f, 0.563f };
		FVector Pos = { 0.0f, 0.024f };
		C_ChangeCharactrer("Cer_Bad.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Cer_Script[2]);

		++OrderCount;
	}
}

void Epilogue::CerCutScene4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[3]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Cer_Script[6]);

		++OrderCount;
	}
}

void Epilogue::CerCutScene5()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.47f, 0.563f };
		FVector Pos = { 0.0f, 0.024f };
		C_ChangeCharactrer("Cer_Bad.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Cer_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Cer_Script[2]);

		++OrderCount;
	}
}

void Epilogue::JudCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Jud_Script[3]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Jud_Script[4]);
}

void Epilogue::JudCutScene()
{
	switch (OrderCount)
	{
	case 0:
		JudCutScene1();
		break;
	case 1:
		JudCutScene2();
		break;
	case 2:
		JudCutScene3();
		break;
	case 3:
		GoBackChapter();
		break;
	}
}

void Epilogue::JudCutScene1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.467f, 0.693f };
		FVector Pos = { 0.0f, -0.042f };
		C_ChangeCharactrer("Jud_Angry.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jud_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jud_Script[1]);

		++OrderCount;
	}
}

void Epilogue::JudCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jud_Script[3]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jud_Script[5]);

		++OrderCount;
	}
}

void Epilogue::JudCutScene3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.415f, 0.682f };
		FVector Pos = { -0.026f, -0.036f };
		C_ChangeCharactrer("Jud_PanCake.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Jud_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Jud_Script[2]);

		++OrderCount;
	}
}

void Epilogue::PolCutSceneStart()
{
	AllCutSceneActorOn();
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 0.416f, 0.584f };
	FVector Pos = { 0.006f, 0.014f };
	C_ChangeCharactrer("Police_001.png", { WinScale * Pos , WinScale * Scale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Pol_Script[0]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Pol_Script[1]);
}

void Epilogue::PolCutScene()
{
	switch (OrderCount)
	{
	case -1:
		GoBackChapter();
		break;
	case 0:
		PolCutScene1();
		break;
	case 1:
		PolCutScene2();
		break;
	case 2:
		PolEndCutScene2();
		break;
	case 3:
		PolEndCutScene3();
		break;
	}
}

void Epilogue::PolCutScene1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		C_MenubarRenderActiveOn();
		C_BooperImageRendererOff();
		C_MenubarTextSet(0, Pol_Script[2]);
		C_MenubarTextSet(1, Pol_Script[3]);

		++OrderCount;
	}
}

void Epilogue::PolEndCutScene1()
{
	C_MenubarRenderActiveOff();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_ChangeCharactrer("Man_PanCake_001.png", { WinScale * ManPos , WinScale * ManScale });
	C_GetSceneCharacter()->GetNameRenderer()->SetText(Pol_Script[6]);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_BooperTextSet(Pol_Script[7]);
	C_BooperImageRendererOn();

	++OrderCount;
}

void Epilogue::PolEndCutScene2()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.376f, 0.625f };
		FVector Pos = { 0.001f, -0.004f };
		C_ChangeCharactrer("Police_002.png", { WinScale * Pos , WinScale * Scale });
		C_GetSceneCharacter()->GetNameRenderer()->SetText(Pol_Script[0]);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(Pol_Script[4]);

		++OrderCount;
	}
}

void Epilogue::PolEndCutScene3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		StateChange(EEpilogueState::Ending);
	}
}

void Epilogue::PolCutScene2()
{
	FocusMenuBarCheck();
}

void Epilogue::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		PolEndCutScene1();
		break;
	case 1:
		PolGoBackChap();
		break;
	}
}

void Epilogue::EndingStart()
{
	C_GetDialogue()->AllRenderersActiveOff();
	C_GetSceneCharacter()->AllRenderersActiveOff();

	C_BooperTextSet("...");

	OrderCount = 0;
}

void Epilogue::Ending()
{
	switch (OrderCount)
	{
	case 0:
		Ending1();
		break;
	case 10:
		Ending3();
		break;
	case 11:
		Ending4();
		break;
	case 12:
		Ending5();
		break;
	case 13:
		GoBackMainMenu();
		break;
	default:
		Ending2();
		break;
	}
}

void Epilogue::Ending1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.67f, 0.6f };
		FVector Pos = { 0.0f, -0.02f };
		C_ChangeDialogue("CutScene_Ending.png", { WinScale * Pos, WinScale * Scale });

		C_BooperTextSet(Ending_Script[0]);
		++OrderCount;
	}
}

void Epilogue::Ending2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Ending_Script[OrderCount]);
		++OrderCount;
	}
}

void Epilogue::Ending3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		TransitionOn();
		++OrderCount;
	}
}

void Epilogue::Ending4()
{
	if (19 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		C_ChangeDialogue("EndingBG.png", { { 0.0f, 0.0f }, WinScale });
		C_GetDialogue()->SetActorLocation(WinScale.Half2D());
		C_BooperTextSet(Ending_Script[10]);
		++OrderCount;
	}
}

void Epilogue::Ending5()
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->AllRenderersActiveOff();
	}

	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		//TransitionOn();
		//++OrderCount;
	}
}

void Epilogue::GoBackMainMenu()
{
	if (19 == GetTransitionActor()->GetImageRenderer()->GetCurAnimationFrame())
	{
		//GEngine->ChangeLevel("MainMenu");
	}
}

void Epilogue::PolGoBackChap()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_MenubarRenderActiveOff();
		C_BooperImageRendererOn();
		C_BooperTextSet(Pol_Script[5]);

		FVector TileScale = ContentsHelper::GetTileScale();
		PlayerHero->SetLocationPoint(PlayerHero->GetLocationPoint() + Point::Up);
		PlayerHero->AddActorLocation(FVector::Up * TileScale.Y);

		OrderCount = -1;
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
	case EEpilogueState::PandCutScene:
		PandCutScene();
		break;
	case EEpilogueState::MalCutScene:
		MalCutScene();
		break;
	case EEpilogueState::ZdCutScene:
		ZdCutScene(_DeltaTime);
		break;
	case EEpilogueState::AzCutScene:
		AzCutScene();
		break;
	case EEpilogueState::CerCutScene:
		CerCutScene();
		break;
	case EEpilogueState::JudCutScene:
		JudCutScene();
		break;
	case EEpilogueState::PolCutScene:
		PolCutScene();
		break;
	case EEpilogueState::Ending:
		Ending();
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
		case EEpilogueState::AzCutScene:
			AzCutSceneStart();
			break;
		case EEpilogueState::CerCutScene:
			CerCutSceneStart();
			break;
		case EEpilogueState::JudCutScene:
			JudCutSceneStart();
			break;
		case EEpilogueState::PolCutScene:
			PolCutSceneStart();
			break;
		case EEpilogueState::Ending:
			EndingStart();
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
const std::vector<const char*> Epilogue::Pand_Script =
{
	/* 0  Demon	   */ "피곤한 악마 판데모니카",
	/* 1  Demon	   */ "가학적인 악마 판데모니카",
	/* 2  Script 1 */ "...",
	/* 3  Script 2 */ "아! 이제 피곤한 악마는 끝났어.",
	/* 4  Script 3 */ "아니... 딱 적당해. 이번엔 여과도 잘 했고.",
	/* 5  Script 4 */ "이대로만 한다면 손가락 멀쩡한 날까지 살아 있겠네.",
	/* 6  Script 5 */ "그렇지만 망치고 싶으면 마음대로 해. 동네 병원이 꽤 용한 것\n같던데.",
	/* 7  Script 6 */ "기억은 네가 하고 있어야지.",

	/* 8  Man	   */ "헬테이커",
	/* 9  Script 1 */ "자 팬케이크랑 커피.",
	/* 10 Script 2 */ "또 너무 진하게 뽑았나?",
	/* 11 Script 3 */ "그래...",
	/* 12 Script 4 */ "다음 건 오후 5시 15분에 더블 에스프레소 맞지?"
};
const std::vector<const char*> Epilogue::Mal_Script =
{
	/* 0 Demon	  */ "시큰둥한 악마 말리나",
	/* 1 Script 1 */ "할 만한 신작 턴제 게임 찾기가 왜 이렇게 힘들어?",
	/* 2 Script 2 */ "무슨 나오는 것들이 죄다 대충 찍어낸 후속작이나 표절작\n투성이야.",
	/* 3 Script 3 */ "참 거지같게도, 나도 그렇긴 해.",
	/* 4 Script 4 */ "술이 꽤 필요하겠지만.",

	/* 5 Man	  */ "헬테이커",
	/* 6 Script 1 */ "자 팬케이크.",
	/* 7 Script 2 */ "그래도 난 할 것 같더라."
};
const std::vector<const char*> Epilogue::Zd_Script =
{
	/* 0 Demon	  */ "상스러운 악마 즈드라다",
	/* 1 Script 1 */ "좋아. 근데 불 좀 썻으면 하는데.",
	/* 2 Script 2 */ "그래서? 벌이라도 주려고? 해 봐, 나 완전 나쁜 여자인데.",
	/* 3 Script 3 */ "확 꺼져.",

	/* 4 Man	  */ "헬테이커",
	/* 5 Script 1 */ "자 팬케이크.",
	/* 6 Script 2 */ "실내에선 금연이야.",
	/* 7 Script 3 */ "벌을 즐기는 거 아니야?"
};
const std::vector<const char*> Epilogue::Az_Script =
{
	/* 0  Demon	   */ "호기심 많은 천사 아자젤",
	/* 1  Script 1 */ "제가 얼마동안 있었죠?",
	/* 2  Script 2 */ "참 오랫동안 지낸 것 같아요.",
	/* 3  Script 3 */ "내가 본 것들...",
	/* 4  Script 4 */ "내가 한 것들...",
	/* 5  Script 5 */ "이걸로 획기적인 논문을 쓸 수는 있겠지만, 아무도 안 믿겠죠.\n너무 초현실적이에요.",
	/* 6  Script 6 */ "그리고 이건 겉핥기에 불과하죠. 오늘 연구를 같이 하실래요?",

	/* 7  Man	   */ "헬테이커",
	/* 8  Script 1 */ "자 팬케이크.",
	/* 9  Script 2 */ "몇 주 정도.",
	/* 10 Script 3 */ "아...",
	/* 11 Script 4 */ "연구를 너무 많이 하잖아. 팬케이크나 좀 먹어."
};
const std::vector<const char*> Epilogue::Cer_Script =
{
	/* 0 Demon	  */ "세 쌍둥이 악마 케르베로스",
	/* 1 Script 1 */ "망했어.",
	/* 2 Script 2 */ "...",

	/* 3 Man	  */ "헬테이커",
	/* 4 Script 1 */ "자 팬케이크.",
	/* 5 Script 2 */ "또 이웃집에 사고 쳤어? 뭘 했길래?",
	/* 6 Script 3 */ "경찰은 문 앞에 왜 와 있고?"
};
const std::vector<const char*> Epilogue::Jud_Script =
{
	/* 0 Demon	  */ "고위 기소관 저지먼트",
	/* 1 Script 1 */ "침입자가 우리의 영역을 침범하려 한다! 내가 처리할까?",
	/* 2 Script 2 */ "그래, 재미나 봐.",

	/* 3 Man	  */ "헬테이커",
	/* 4 Script 1 */ "자 팬케이크.",
	/* 5 Script 2 */ "그럴 필요 없어. 내가 할게."
};
const std::vector<const char*> Epilogue::Pol_Script =
{
	/* 0 Demon	   */ "경찰",
	/* 1 Script 1  */ "경찰입니다! 문 여십시오.",
	/* 2 Menubar 1 */ "연다. (게임을 끝낸다.)",
	/* 3 Menubar 2 */ "열지 않는다.",

	/* 4 Script 2  */ "아, 감사합니다. 몇 가지 물어볼 게 있습니다.",
	/* 5 Script 3  */ "안에 계신 거 압니다! 빨리 문 여십시오!",

	/* 6 Man	   */ "헬테이커",
	/* 7 Script 1  */ "팬케이크라도 드시겠습니까?"
};
const std::vector<const char*> Epilogue::Ending_Script =
{
	/* 0  Script 1   */ "그리하여 헬테이커의 이야기는 끝이 났지.",
	/* 1  Script 2   */ "오랜 친구 베엘제붑이 들려주었다네.",
	/* 2  Script 3   */ "나도 바보같은 이야기인 건 알지만..",
	/* 3  Script 4   */ "솔직히 말하자면... 사실 불쾌하고 혐오스러운 이야기지.",
	/* 4  Script 5   */ "불쾌한 사람들에 대한 불쾌한 이야기.",
	/* 5  Script 6   */ "하지만 어쩌면... 일말의 행복은 찾을 수 있지 않을까.",
	/* 6  Script 7   */ "한 두번 정도는 웃을 수 있겠지?",
	/* 7  Script 8   */ "그럼... 늙은 파리와 함께 해줘서 고마웠네.",
	/* 8  Script 9   */ "그럼 다음에.",
	/* 9  Script 10  */ "THE END",
	/* 10 Script 11  */ "플레이 해주셔서 감사합니다!\n[모작자 - 김수원]"
};
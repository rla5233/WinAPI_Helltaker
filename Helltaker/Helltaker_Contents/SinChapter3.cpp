#include "SinChapter3.h"

#include "Sin_Judge.h"
#include "UI.h"

#include "SinChapter4.h"

bool SinChapter3::IsLoad = false;
const std::vector<const char*> SinChapter3::SinChap3_Script =
{
	/* 0  Demon	   */ "고위 기소관 저지먼트",
	/* 1 Script 1  */ "진정 사슬을 부수고 빠져나갈 수 있을 것 같느냐?",
	/* 2 Script 2  */ "희망은 실망을, 그리고 실망은 절망을 낳는다.",
	/* 3 Script 3  */ "그리고 절망의 사슬이 가장 즐거운 법이지.",
	/* 4 Script 4  */ "그래! 네가 행한 모든 것들을 후회하라!",

	/* 5 MenuBar 1  */ "니 헤어 스타일이 마음에 드는데.",
  	/* 6 MenuBar 2  */ "그 옷 끝내주는데! 10점 만점에 10점!",
	/* 7 Script 1   */ "거짓말! 기만으로 네 운명을 벗어날 수는 없다!",

	/* 8 MenuBar 1  */ "알아. 그래서 내가 솔직한 거지.",
	/* 9 MenuBar 2  */ "그 손톱도 마음에 들어!",
	/* 10 Script 1  */ "그래? 그렇다면, '고맙다!'라고 해야겠지?",
	/* 11 Script 2  */ "이제 다시 시련을 시작한다!",

	/* 12  Demon	*/ "상스러운 악마 즈드라다",
	/* 13 Script 1  */ "말린카는 재수도 없지. 기껏 찾은 겜스퍼거 친구가 죽게\n생겼네.",

	/* 14  Demon	*/ "시큰둥한 악마 말리나",
	/* 15 Script 1  */ "내 운수가 이러니 쟤가 네크로폴리스를 하게 됐어.",

	/* 16 Demon	    */ "음란한 악마 모데우스",
	/* 17 Script 1  */ "차라리 나 혼자 독차지할 걸...",
};

SinChapter3::SinChapter3()
{
}

SinChapter3::~SinChapter3()
{
}

void SinChapter3::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_BindAnim_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_BindAnim_002.png");
		ContentsHelper::LoadImg("Scene\\Characters\\Jud_Pose", "Jud_PoseAnim_001.png");
		ContentsHelper::LoadImg("Scene\\Characters\\", "PentaGraphic.png");

		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_BindAnim");
		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Pose");
		ContentsHelper::LoadFolder("Scene\\Characters", "Jud_Fly");

		AddChapterSet("SinChapter3");

		IsLoad = true;
	}
}

void SinChapter3::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(3);

	M_StateChange(ESinState::Intro);
}

void SinChapter3::Phase1_Start()
{
	SinChapterManager::Phase1_Start();
	SetPhase1_StartDelayTime(2.0f);

	M_SetSmallChainVecSize(28, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(3, 0);
	
	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);

	M_CreateSmallVerChain_P1(1, 2);
	M_CreateSmallVerChain_P1(5, 2);

	M_CreateSmallVerChain_P1(0, 3);
	M_CreateSmallVerChain_P1(6, 3);

	M_CreateSmallHorChain_P1(4, 5);
	
	M_CreateSmallHorChain_P1(2, 6);

	M_CreateSmallVerChain_P1(0, 7);
	M_CreateSmallVerChain_P1(6, 7);

	M_CreateSmallHorChain_P1(0, 8);

	M_CreateSmallVerChain_P1(1, 9);
	M_CreateSmallVerChain_P1(5, 9);

	M_CreateSmallHorChain_P1(4, 10);

	M_CreateSmallVerChain_P1(2, 11);
	M_CreateSmallVerChain_P1(4, 11);

	M_CreateSmallHorChain_P1(1, 12);

	M_CreateSmallVerChain_P1(3, 13);
	
	M_CreateSmallVerChain_P1(0, 15);
	M_CreateSmallVerChain_P1(3, 15);
	M_CreateSmallVerChain_P1(6, 15);

	M_CreateSmallVerChain_P1(1, 16);
	M_CreateSmallVerChain_P1(2, 16);
	M_CreateSmallVerChain_P1(4, 16);
	M_CreateSmallVerChain_P1(5, 16);
	
	M_CreateSmallHorChain_P1(2, 17);

	M_CreateSmallVerChain_P1(0, 18);
	M_CreateSmallVerChain_P1(6, 18);

	M_CreateSmallVerChain_P1(3, 19);
	M_CreateSmallHorChain_P1(0, 19);
	M_CreateSmallHorChain_P1(4, 19);

	M_CreateSmallVerChain_P1(2, 20);
	M_CreateSmallVerChain_P1(4, 20);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(6, 21);
	M_CreateSmallHorChain_P1(1, 21);

	M_CreateSmallVerChain_P1(1, 22);
	M_CreateSmallVerChain_P1(5, 22);

	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallHorChain_P1(4, 23);

	M_CreateSmallVerChain_P1(2, 24);
	M_CreateSmallVerChain_P1(3, 24);
	M_CreateSmallVerChain_P1(4, 24);

	M_CreateSmallVerChain_P1(1, 25);
	M_CreateSmallVerChain_P1(2, 25);
	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallVerChain_P1(4, 25);
	M_CreateSmallVerChain_P1(5, 25);

	M_CreateSmallVerChain_P1(0, 26);
	M_CreateSmallVerChain_P1(6, 26);

	M_CreateSmallVerChain_P1(0, 27);
	M_CreateSmallVerChain_P1(1, 27);
	M_CreateSmallVerChain_P1(5, 27);
	M_CreateSmallVerChain_P1(6, 27);
}

void SinChapter3::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 0);
	M_CreateHitChain(ESinHitChainType::Right, 2);
	M_CreateHitChainHp("3. 욕정의 사슬");

	M_SetSmallChainVecSize(4, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(1, 0);
	M_CreateSmallHorChain_P2(0, 0);

	M_CreateSmallHorChain_P2(0, 1);
	M_CreateSmallHorChain_P2(4, 1);

	M_CreateSmallVerChain_P2(5, 2);
	M_CreateSmallVerChain_P2(6, 2);
	M_CreateSmallHorChain_P2(4, 2);

	M_CreateSmallVerChain_P2(0, 3);
	M_CreateSmallVerChain_P2(6, 3);
}

void SinChapter3::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();

	C_SpawnDialogue(1);

	FVector Scale = { 0.658f, 0.693f };
	FVector Pos = { 0.0f, -0.042f };
	C_SpawnJudge("Jud_BindAnim_001.png", SinChap3_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap3_Script[1]);
}

void SinChapter3::EnterStart()
{
	OrderCount = 0;
}

void SinChapter3::Enter(float _DeltaTime)
{
	SinCutSceneManager::Enter(_DeltaTime);

	switch (OrderCount)
	{
	case 0:
		Enter1();
		break;
	case 1:
		Enter2();
		break;
	case 2:
		Enter3();
		break;
	case 3:
		Enter4();
		break;
	case 4:
		Enter5();
		break;
	case 5:
		Enter6();
		break;
	case 6:
		Enter7();
		break;
	}
}

void SinChapter3::Enter1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		// 수정 (jud 애니메이션 추가)
		C_BooperTextSet(SinChap3_Script[2], true);
		++OrderCount;
	}
}

void SinChapter3::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.247f, 0.561f };
		FVector Pos = { 0.015f, 0.02f };
		// 수정 (jud 애니메이션 추가)

		C_BooperTextSet(SinChap3_Script[3], true);
		++OrderCount;
	}
}

void SinChapter3::Enter3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetJudge()->AllRenderersActiveOff();

		FVector Scale = { 0.256f, 0.567f };
		FVector Pos = { 0.014f, 0.021f };
		C_SpawnCharacter("Zd", "Zd_Idle.png", SinChap3_Script[12], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[13], true);
		++OrderCount;
	}
}

void SinChapter3::Enter4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.21f, 0.576f };
		FVector Pos = { 0.0f, 0.017f };
		C_CharacterChange("Mal", "Mal_Puzzled.png", SinChap3_Script[14], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[15], true);
		++OrderCount;
	}
}

void SinChapter3::Enter5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.194f,  0.605f };
		FVector Pos = { 0.0f, 0.0f };
		C_CharacterChange("Mod", "Mod_Idle.png", SinChap3_Script[16], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[17], true);
		++OrderCount;
	}
}

void SinChapter3::Enter6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetSceneCharacter()->AllRenderersActiveOff();

		FVector Scale = { 0.558f, 0.693f };
		FVector Pos = { 0.0f, -0.0402f };
		C_JudgeChange("Jud_Intro_004.png", Pos, Scale);
		C_GetJudge()->AllRenderersActiveOn();
		C_GetJudge()->Character::StateChange(ECharacterState::None);
		C_GetJudge()->Character::StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap3_Script[4], true);
		++OrderCount;
	}
}

void SinChapter3::Enter7()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		UEngineSound::SoundPlay("booper_click.wav");
		C_StateChange(ESinSceneState::Select);
	}
}

void SinChapter3::SelectStart()
{
	SinCutSceneManager::SelectStart();

	C_MenubarTextSet(0, SinChap3_Script[5]);
	C_MenubarTextSet(1, SinChap3_Script[6]);
	OrderCount = 0;
}

void SinChapter3::SelectMenu()
{
	switch (OrderCount)
	{
	case 0:
		Select1();
		break;
	case 1:
		Select2();
		break;
	case 2:
		Select3();
		break;
	case 3:
		Select4();
		break;
	}
}


void SinChapter3::Select1()
{
	UEngineSound::SoundPlay("dialogue_button_confirm.wav");
	C_MenubarRenderActiveOff();
	C_BooperTextSet(SinChap3_Script[7]);
	C_GetBooper()->AllRenderersActiveOn();
	++OrderCount;
}

void SinChapter3::Select2()
{
	UEngineSound::SoundPlay("booper_click.wav");
	C_GetBooper()->GetImageRenderer()->ActiveOff();
	C_MenubarTextSet(0, SinChap3_Script[8]);
	C_MenubarTextSet(1, SinChap3_Script[9]);
	C_MenubarRenderActiveOn();
	++OrderCount;
}

void SinChapter3::Select3()
{
	UEngineSound::SoundPlay("dialogue_button_confirm.wav");
	C_GetBooper()->GetImageRenderer()->ActiveOn();

	FVector Scale = { 0.39f, 0.693f };
	FVector Pos = { 0.0f, -0.04f };
	C_JudgeChange("Jud_PoseAnim_001.png", Pos, Scale);
	C_BooperTextSet(SinChap3_Script[10]);
	C_MenubarRenderActiveOff();
	++OrderCount;
}

void SinChapter3::Select4()
{
	C_BooperTextSet(SinChap3_Script[11], true);
	C_GetJudge()->StateChange(ESinJudgeState::Chap3_Fly);
	C_StateChange(ESinSceneState::End);
}

void SinChapter3::ChangeChapter()
{
	SinManager::ChangeChapter();

	CreateChapter<SinChapter4>("SinChapter4");
	GEngine->ChangeLevel("SinChapter4");
}

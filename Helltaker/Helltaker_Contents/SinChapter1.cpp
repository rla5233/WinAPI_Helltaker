#include "SinChapter1.h"

#include "SinChapter2.h"
#include "Sin_Judge.h"

bool SinChapter1::IsLoad = false;
const std::vector<const char*> SinChapter1::SinChap1_Script =
{
	/* 0  Demon	    */ "고위 기소관 저지먼트",
	/* 1  Script 1  */ "침입자야, 죄악의 기계가 마음에 드느냐?",
	/* 2  Script 2  */ "이만 굴복하고 삼켜져라!",
	/* 3  Script 3  */ "희망을 버려라! 저 녀석의 운명은 이미 정해졌다!",
	/* 4  Script 4  */ "정숙하라! 이제 진짜 시작이다!",

	/* 5  Demon	    */ "세 쌍둥이 악마 케르베로스",
	/* 6  Script 1  */ "안돼, 포기하지 마! 우릴 데리고 나가야지!",

	/* 7  Demon	    */ "피곤한 악마 판데모니카",
	/* 8  Script 1  */ "그리고 커피도 타 주셔야죠.",

	/* 9  Demon	    */ "지옥의 CEO 루시퍼",
	/* 10 Script 1  */ "이런, 저지먼트. 이 녀석은 모르고 있겠지만, 내 거야. 그냥\n내버려 둘 수는 없어?",
};

SinChapter1::SinChapter1()
{
}

SinChapter1::~SinChapter1()
{
}

void SinChapter1::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters\\Jud_Intro", "Jud_Intro_004.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Back.png");

		AddChapterSet("SinChapter1");
		IsLoad = true;
	}
}

void SinChapter1::LevelStart(ULevel* _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(1);

	M_StateChange(ESinState::Intro);
}

void SinChapter1::Phase1_Start()
{
	SinChapterManager::Phase1_Start();

	M_SetSmallChainVecSize(26, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(0, 0);

	M_CreateSmallVerChain_P1(1, 1);
	
	M_CreateSmallVerChain_P1(2, 2);
	
	M_CreateSmallVerChain_P1(3, 3);
	
	M_CreateSmallVerChain_P1(4, 4);
	
	M_CreateSmallVerChain_P1(6, 6);
	
	M_CreateSmallVerChain_P1(5, 7);
	
	M_CreateSmallVerChain_P1(4, 8);
	
	M_CreateSmallVerChain_P1(3, 9);

	M_CreateSmallVerChain_P1(2, 10);
	
	M_CreateSmallVerChain_P1(0, 12);
	
	M_CreateSmallVerChain_P1(2, 13);
	
	M_CreateSmallVerChain_P1(4, 14);
	
	M_CreateSmallVerChain_P1(1, 15);
	M_CreateSmallVerChain_P1(6, 15);
	
	M_CreateSmallVerChain_P1(0, 16);
	M_CreateSmallVerChain_P1(3, 16);
	
	M_CreateSmallVerChain_P1(2, 17);
	M_CreateSmallVerChain_P1(5, 17);
	
	M_CreateSmallVerChain_P1(4, 18);
	
	M_CreateSmallVerChain_P1(6, 19);
	
	M_CreateSmallVerChain_P1(3, 21);
	
	M_CreateSmallVerChain_P1(0, 22);
	M_CreateSmallVerChain_P1(6, 22);
	
	M_CreateSmallVerChain_P1(2, 23);
	M_CreateSmallVerChain_P1(4, 23);
	
	M_CreateSmallVerChain_P1(1, 24);
	M_CreateSmallVerChain_P1(5, 24);
	
	M_CreateSmallVerChain_P1(0, 25);
	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallVerChain_P1(6, 25);
}

void SinChapter1::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 1);
	M_CreateHitChain(ESinHitChainType::Right, 1);
	M_CreateHitChainHp("1. 교만의 사슬");
}

void SinChapter1::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();
	
	C_SpawnDialogue(1);

	FVector Scale = { 0.558f, 0.693f };
	FVector Pos = { 0.0f, -0.0402f };
	C_SpawnJudge("Jud_Intro_004.png", SinChap1_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap1_Script[1]);
}

void SinChapter1::EnterStart()
{
	OrderCount = 0;
}

void SinChapter1::Enter(float _DeltaTime)
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
	}
}

void SinChapter1::Enter1()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetJudge()->IsImgMoveOn()))
	{
		C_BooperTextSet(SinChap1_Script[2], true);
		++OrderCount;
	}
}

void SinChapter1::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetJudge()->AllRenderersActiveOff();

		FVector Scale = { 0.503f, 0.576f };
		FVector Pos = { 0.0f, 0.0175f };
		C_SpawnCharacter("Cer", "Cer_Idle.png", SinChap1_Script[5], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap1_Script[6], true);
		++OrderCount;
	}
}

void SinChapter1::Enter3()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		FVector Scale = { 0.255f, 0.611f };
		FVector Pos = { -0.009f, 0.0f };
		C_CharacterChange("Pand", "Pand_Flust.png", SinChap1_Script[7], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap1_Script[8], true);
		++OrderCount;
	}
}

void SinChapter1::Enter4()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		C_GetSceneCharacter()->AllRenderersActiveOff();

		FVector Scale = { 0.4667f, 0.692f };
		FVector Pos = { 0.0f, -0.0418f };
		C_JudgeChange("Jud_Back.png", Pos, Scale);
		C_GetJudge()->AllRenderersActiveOn();
		C_GetJudge()->Character::StateChange(ECharacterState::None);
		C_GetJudge()->Character::StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap1_Script[3], true);
		++OrderCount;
	}
}

void SinChapter1::Enter5()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetJudge()->IsImgMoveOn()))
	{
		C_GetJudge()->AllRenderersActiveOff();

		FVector Scale = { 0.247f, 0.561f };
		FVector Pos = { 0.015f, 0.02f };
		C_CharacterChange("Lu", "Lu_Angry.png", SinChap1_Script[9], Pos, Scale);
		C_GetSceneCharacter()->AllRenderersActiveOn();
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap1_Script[10], true);
		++OrderCount;
	}
}

void SinChapter1::Enter6()
{
	if ((UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
		&& (false == C_GetSceneCharacter()->IsImgMoveOn()))
	{
		C_GetSceneCharacter()->AllRenderersActiveOff();

		FVector Scale = { 0.4666f, 0.692f };
		FVector Pos = { 0.0f, -0.042f };
		C_JudgeChange("Jud_Angry.png", Pos, Scale);
		C_GetJudge()->AllRenderersActiveOn();
		C_GetJudge()->Character::StateChange(ECharacterState::None);
		C_GetJudge()->Character::StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap1_Script[4], true);
		C_StateChange(ESinSceneState::End);
	}
}

void SinChapter1::ChangeChapter()
{
	SinManager::ChangeChapter();

	CreateChapter<SinChapter2>("SinChapter2");
	GEngine->ChangeLevel("SinChapter2");
}

#include "SinChapter2.h"

#include "Sin_Judge.h"

#include "SinChapter3.h"

bool SinChapter2::IsLoad = false;
const std::vector<const char*> SinChapter2::SinChap2_Script =
{
	/* 0  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 1  Script 1  */ "�ʸ� �̰����� �̲����� �͵��� �罽�� �Ǿ� �ʸ� �ְ���.",
	/* 2  Script 2  */ "���� ����, Ž��, �׸��� ����. �� ������ ������ �Ŵ�.",
	/* 3  Script 3  */ "�� � ������ ������ �Ѿ �� ����!",

	/* 4  Demon	    */ "������ CEO �����",
	/* 5  Script 1  */ "�׸�! ���� ��Ұ�, ��� ������ ���� ���Ѵ�!",
	/* 6  Script 2  */ "�� ���� ����! ���� ������ �����̶��! �� �ƹ��� ������\n�ȵ�°ž�!",

	/* 7  Demon	    */ "�����ִ� �Ǹ� ����Ƽ��",
	/* 8  Script 1  */ "������Ʈ, ��� �� ��! �� �����µ�!",
				   
	/* 9  Demon	    */ "ȣ��� ���� õ�� ������",
	/* 10 Script 1  */ "�׷���, ����ϼ���. �̰� �и� A+ ���� ���� ���翡��.",
};

SinChapter2::SinChapter2()
{
}

SinChapter2::~SinChapter2()
{
}

void SinChapter2::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Characters", "Jud_Laugh.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Rustled.png");

		AddChapterSet("SinChapter2");

		IsLoad = true;
	}
}

void SinChapter2::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(2);

	M_StateChange(ESinState::Intro);
}

void SinChapter2::Phase1_Start()
{
	SinChapterManager::Phase1_Start();

	M_SetSmallChainVecSize(25, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(0, 0);
	M_CreateSmallVerChain_P1(3, 0);
	M_CreateSmallVerChain_P1(6, 0);

	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);

	M_CreateSmallVerChain_P1(3, 2);

	M_CreateSmallVerChain_P1(2, 3);
	M_CreateSmallVerChain_P1(4, 3);

	M_CreateSmallVerChain_P1(0, 4);
	M_CreateSmallVerChain_P1(3, 4);
	M_CreateSmallVerChain_P1(6, 4);

	M_CreateSmallHorChain_P1(4, 6);

	M_CreateSmallHorChain_P1(2, 7);

	M_CreateSmallHorChain_P1(0, 8);
	M_CreateSmallHorChain_P1(4, 8);

	M_CreateSmallHorChain_P1(2, 9);

	M_CreateSmallHorChain_P1(0, 10);

	M_CreateSmallVerChain_P1(0, 11);
	M_CreateSmallVerChain_P1(6, 11);

	M_CreateSmallVerChain_P1(0, 12);
	M_CreateSmallVerChain_P1(1, 12);
	M_CreateSmallVerChain_P1(5, 12);
	M_CreateSmallVerChain_P1(6, 12);

	M_CreateSmallVerChain_P1(3, 13);

	M_CreateSmallVerChain_P1(2, 14);
	M_CreateSmallVerChain_P1(3, 14);
	M_CreateSmallVerChain_P1(4, 14);

	M_CreateSmallVerChain_P1(0, 15);
	M_CreateSmallVerChain_P1(2, 15);
	M_CreateSmallVerChain_P1(4, 15);
	M_CreateSmallVerChain_P1(6, 15);

	M_CreateSmallVerChain_P1(1, 16);
	M_CreateSmallVerChain_P1(3, 16);
	M_CreateSmallVerChain_P1(5, 16);

	M_CreateSmallVerChain_P1(0, 17);
	M_CreateSmallVerChain_P1(6, 17);

	M_CreateSmallVerChain_P1(2, 18);
	M_CreateSmallVerChain_P1(4, 18);

	M_CreateSmallVerChain_P1(1, 19);
	M_CreateSmallVerChain_P1(3, 19);
	M_CreateSmallVerChain_P1(5, 19);

	M_CreateSmallVerChain_P1(0, 20);
	M_CreateSmallVerChain_P1(6, 20);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(1, 21);
	M_CreateSmallVerChain_P1(3, 21);
	M_CreateSmallVerChain_P1(5, 21);
	M_CreateSmallVerChain_P1(6, 21);

	M_CreateSmallVerChain_P1(2, 22);
	M_CreateSmallVerChain_P1(4, 22);

	M_CreateSmallVerChain_P1(1, 23);
	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallVerChain_P1(5, 23);

	M_CreateSmallVerChain_P1(0, 24);
	M_CreateSmallVerChain_P1(3, 24);
	M_CreateSmallVerChain_P1(6, 24);
}

void SinChapter2::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 2);
	M_CreateHitChain(ESinHitChainType::Right, 0);
	M_CreateHitChainHp("2. Ž���� �罽");

	M_SetSmallChainVecSize(3, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(6, 0);

	M_CreateSmallVerChain_P2(1, 1);
	M_CreateSmallVerChain_P2(5, 1);

	M_CreateSmallVerChain_P2(2, 2);
	M_CreateSmallVerChain_P2(4, 2);
}

void SinChapter2::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();

	C_SpawnDialogue(1);

	FVector Scale = { 0.416f, 0.693f };
	FVector Pos = { 0.0f, -0.0502f };
	C_SpawnJudge("Jud_Laugh.png", SinChap2_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap2_Script[1]);
}

void SinChapter2::EnterStart()
{
	OrderCount = 0;
}

void SinChapter2::Enter(float _DeltaTime)
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

void SinChapter2::Enter1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(SinChap2_Script[2], true);
		++OrderCount;
	}
}

void SinChapter2::Enter2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetJudge()->AllRenderersActiveOff();

		FVector Scale = { 0.247f, 0.561f };
		FVector Pos = { 0.015f, 0.02f };
		C_SpawnCharacter("Lu", "Lu_Angry.png", SinChap2_Script[4], Pos, Scale);
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap2_Script[5], true);
		++OrderCount;
	}
}

void SinChapter2::Enter3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetSceneCharacter()->AllRenderersActiveOff();

		FVector Scale = { 0.4666f, 0.692f };
		FVector Pos = { 0.0f, -0.042f };
		C_JudgeChange("Jud_Angry.png", Pos, Scale);
		C_GetJudge()->AllRenderersActiveOn();
		C_GetJudge()->Character::StateChange(ECharacterState::None);
		C_GetJudge()->Character::StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap2_Script[3], true);
		++OrderCount;
	}
}

void SinChapter2::Enter4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_GetJudge()->AllRenderersActiveOff();
			
		FVector Scale = { 0.22f, 0.612f };
		FVector Pos = { 0.0f, 0.0f };
		C_CharacterChange("Jus", "Jus_Idle.png", SinChap2_Script[7], Pos, Scale);
		C_GetSceneCharacter()->AllRenderersActiveOn();
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap2_Script[8], true);
		++OrderCount;
	}
}

void SinChapter2::Enter5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.211f, 0.516f };
		FVector Pos = { -0.007f, 0.03f };
		C_CharacterChange("Az", "Az_Note.png", SinChap2_Script[9], Pos, Scale);
		
		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap2_Script[10], true);
		++OrderCount;
	}
}

void SinChapter2::Enter6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector Scale = { 0.279f, 0.692f };
		FVector Pos = { 0.0f, -0.04f };
		C_CharacterChange("Lu", "Lu_Rustled.png", SinChap2_Script[4], Pos, Scale);

		C_GetSceneCharacter()->StateChange(ECharacterState::None);
		C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

		C_BooperTextSet(SinChap2_Script[6], true);
		C_StateChange(ESinSceneState::End);
	}
}

void SinChapter2::ChangeChapter()
{
	SinManager::ChangeChapter();

	CreateChapter<SinChapter3>("SinChapter3");
	GEngine->ChangeLevel("SinChapter3");
}


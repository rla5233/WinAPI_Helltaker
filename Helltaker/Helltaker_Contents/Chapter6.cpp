#include "Chapter6.h"

#include "BackGround.h"
#include "Character.h"
#include "UI.h"
#include "Chapter7.h"

#include <EnginePlatform/EngineSound.h>

bool Chapter6::IsLoad = false;

const std::vector<const char*> Chapter6::Chap6_Script
{
	/* 0 Demon	  */ "ȣ��� ���� õ�� ������",
	/* 1 Script 1 */ "�ϴ��� ���һ�! ����ִ� �ΰ��� �������� �� �ϰ� �ִ� ����?\n��ġ ���� ���̳׿�.",
	/* 2 MenuBar1 */ "�Ǹ��� ã�� �־�.",
	/* 3 MenuBar2 */ "õ�縦 ã�� �־�.",
	/* 4 Failed	  */ "���⼱ ã�� ����ſ���. ������ ���� ���� ���� �˰� ����.\n��, ���� ��������.",
	/* 5 Bad End  */ "������ ������ õ���� ������� ���� �����̳� ������.",
	/* 6 Bad End  */ "�Ǹ� �Ϸ����� ���� �̺�������.",
	/* 7 Success  */ "��, ���ʵ���? Ȥ��, ���� �˾� ���� ���ΰ���? �ƴϸ�\n�Ǹ���? ���� �ϴ°� ���ھ��."
};

Chapter6::Chapter6()
{
}

Chapter6::~Chapter6()
{
}

void Chapter6::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_006.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Az_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Az_Note.png");
		ContentsHelper::LoadImg("Scene\\CutScene", "CutScene_AngelEnd.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Azazel");

		AddChapterSet("Chapter6");
		IsLoad = true;
	}
}

void Chapter6::LevelStart(ULevel* _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, true , true , true , false, false, false },
		{ false, true , true , true , false, false, false },
		{ true , true , true , true , false, false, false },
		{ false, true , true , true , true , false, false },
		{ false, true , false, true , true , true , true  },
		{ false, true , true , true , true , true , false },
		{ false, false, false, false, true , true , true  },
		{ false, false, false, false, true , true , false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.32f, 0.113f });

	CreateBG("ChapterBG_006");
	M_CreateChapterUI(6);

	M_SpawnHero({ 2, 0 }, 43);

	M_SpawnSkeleton({ 1, 4 });
	M_SpawnSkeleton({ 5, 5 });

	M_SetIsThornChange(true);
	M_SpawnThorn({ 1, 3 }, EThornState::Down);
	M_SpawnThorn({ 2, 3 }, EThornState::Down);

	M_SpawnStone({ 1, 1 }, "Stone_006.png");
	M_SpawnStone({ 2, 1 }, "Stone_005.png");
	M_SpawnStone({ 3, 1 }, "Stone_004.png");
	M_SpawnStone({ 2, 3 }, "Stone_003.png");
	M_SpawnStone({ 3, 4 }, "Stone_002.png");
	M_SpawnStone({ 4, 4 }, "Stone_009.png");
	M_SpawnStone({ 3, 5 }, "Stone_008.png");
	M_SpawnStone({ 5, 6 }, "Stone_010.png");

	M_SpawnKeyComponent({ 3, 2 }, EKeyComponentType::Key);
	M_SpawnKeyComponent({ 4, 6 }, EKeyComponentType::LockBox);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.049f, WinScale.Y * 0.08f };
	FVector Pos = { WinScale.X * (-0.002f), WinScale.Y * (-0.007f) };
	M_SpawnDemon({ 5, 7 }, "Azazel", { Pos, Scale });

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter6::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");

	FVector Scale = { 0.235f, 0.591f };
	FVector Pos = { 0.0f, 0.01f };
	C_SpawnCharacter("Az", "Az_Idle.png", Chap6_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);
	
	C_SpawnBooper();
	C_BooperTextSet(Chap6_Script[1]);
}

void Chapter6::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap6_Script[2]);
	C_MenubarTextSet(1, Chap6_Script[3]);
}

void Chapter6::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		C_StateChange(ECutSceneState::Success);
		break;
	case 1:
		C_StateChange(ECutSceneState::BadEnd);
		break;
	}
}

void Chapter6::FailOrderCheck()
{
	switch (C_GetFailOrder())
	{
	case 0:
		FailOrderInputCheck();
		break;
	case 1:
		BadEndSetting1();
		break;
	case 2:
		BadEndSetting2();
		break;
	case 3:
		ChapterRestart();
		break;
	}
}

void Chapter6::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap6_Script[4]);
}

void Chapter6::BadEndSetting1()
{
	for (AActor* Actor : AllCutSceneActors)
	{
		if (nullptr != dynamic_cast<BackGround*>(Actor))
		{
			continue;
		}

		Actor->AllRenderersActiveOff();
	}

	Booper->AllRenderersActiveOn();
	C_BooperTextSet(Chap6_Script[5]);
	UEngineSound::SoundPlay("booper_click.wav");
	C_AddFailOrder(1);
}

void Chapter6::BadEndSetting2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { WinScale.X * 0.67f, WinScale.Y * 0.6f };
		C_ChangeDialogue("CutScene_AngelEnd.png", { {0, 0}, Scale });

		C_BooperTextSet(Chap6_Script[6]);
		UEngineSound::SoundPlay("booper_click.wav");
		C_AddFailOrder(1);
	}
}

void Chapter6::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.211f, WinScale.Y * 0.516f };
	FVector Pos = { WinScale.X * (-0.007f), WinScale.Y * (0.03f) };
	C_CharacterSetTransform({ Pos, Scale });
	C_CharacterSetImage("Az_Note.png");
	C_BooperTextSet(Chap6_Script[7]);
}

void Chapter6::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter7>("Chapter7");
	GEngine->ChangeLevel("Chapter7");
}
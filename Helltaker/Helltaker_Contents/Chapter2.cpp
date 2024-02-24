#include "Chapter2.h"

#include "Chapter3.h"

bool Chapter2::IsLoad = false;

const std::vector<const char*> Chap2_Script
{
	/* 0 Demon	  */ "������ �Ǹ� �𵥿콺",
	/* 1 Script 1 */ "�ʶ� ����.���� �ٷ�.",
	/* 2 MenuBar1 */ "����. ���� ����.",
	/* 3 MenuBar2 */ "�ð� ����.���ھֵ� ������ �ٺ�",
	/* 4 Failed	  */ "�ٵ� �׷��� ���ϰ�... ���߿� �������� �ϴ���.\n Ȥ�� �𸣴� ������ �ν� ������.",
	/* 5 Bad End  */ "�𵥿콺�� Ŀ�ٶ� ��ġ�� ���´�. ���� ���� �� �� �� ����.",
	/* 6 Success  */ "�Ǹ� �Ϸ�? �ҽ��� ��û��... �Ǹ����� �ʸ� ������ ���� ���� �ٵ�,\n�װ� ��ĥ �� ����."
};

Chapter2::Chapter2()
{
}

Chapter2::~Chapter2()
{
}

void Chapter2::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_002.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Close.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Modeus");

		AddChapterSet("Chapter2");
		IsLoad = true;
	}	
}

void Chapter2::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, true , true , true , true, false, false },
		{ false, true , false, true , true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ false, false, false, false, true, true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.318f, 0.208f });

	CreateBG("ChapterBG_002");
	M_CreateChapterUI(2);

	M_SpawnHero({ 0, 4 }, 24);

	M_SpawnSkeleton({ 1, 1 });
	M_SpawnSkeleton({ 5, 4 });
	M_SpawnSkeleton({ 6, 5 });

	M_SpawnStone({ 4, 2 }, "Stone_003.png");
	M_SpawnStone({ 5, 2 }, "Stone_005.png");
	M_SpawnStone({ 6, 2 }, "Stone_007.png");

	M_SetIsThornChange(false);
	M_SpawnThorn({ 1, 2 }, EThornState::Up);
	M_SpawnThorn({ 3, 1 }, EThornState::Up);
	M_SpawnThorn({ 4, 1 }, EThornState::Up);
	M_SpawnThorn({ 4, 2 }, EThornState::Up);
	M_SpawnThorn({ 5, 2 }, EThornState::Up);
	M_SpawnThorn({ 5, 3 }, EThornState::Up);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.048f, WinScale.Y * 0.08f };
	FVector Pos = { 0.0f, WinScale.Y * (-0.01f) };
	M_SpawnDemon({ 4, 5 }, "Modeus", { Pos, Scale });

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter2::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("Mod", "Mod_Idle.png", Chap2_Script[0]);
	C_SpawnBooper();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0, 0 }, { WinScale.X * 0.194f, WinScale.Y * 0.605f } });
	C_BooperTextSet(Chap2_Script[1]);
}

void Chapter2::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap2_Script[2]);
	C_MenubarTextSet(1, Chap2_Script[3]);
}

void Chapter2::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		C_StateChange(ECutSceneState::BadEnd);
		break;
	case 1:
		C_StateChange(ECutSceneState::Success);
		break;
	}
}

void Chapter2::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap2_Script[4]);
}

void Chapter2::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap2_Script[5]);
}

void Chapter2::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0, 0 }, { WinScale.X * 0.252f, WinScale.Y * 0.613f } });
	C_CharacterSetImage("Mod_Close.png");
	C_BooperTextSet(Chap2_Script[6]);
}

void Chapter2::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter3>("Chapter3");
	GEngine->ChangeLevel("Chapter3");
}
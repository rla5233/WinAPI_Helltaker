#include "Chapter5.h"

#include "Chapter6.h"

bool Chapter5::IsLoad = false;

const std::vector<const char*> Chap5_Script
{
	/* 0 Demon	  */ "�󽺷��� �Ǹ� �����",
	/* 1 Script 1 */ "��, �Ϸ� �ٸ��ٰ� ����µ�. ���� ����.",
	/* 2 MenuBar1 */ "���. ���߿� ��ȸ�� �� ���� ����ε�.",
	/* 3 MenuBar2 */ "��� �Ϸ������� ����ġ����. ���� ���� �����̳� �� �ž�.",
	/* 4 Failed	  */ "��� ��. �� ������ �����ٰ�.",
	/* 5 Bad End  */ "����� ���̿� �ڷ� ����� ���� Į�� ������ ����� �þߴ� �������.",
	/* 6 Success  */ "�� ������ �׷��� �� �ž�. ���� �׸� ���� ������."
};

Chapter5::Chapter5()
{
}

Chapter5::~Chapter5()
{
}

void Chapter5::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_005.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Zd_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Zd_Laugh.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Zdrada");

		AddChapterSet("Chapter5");
		IsLoad = true;
	}
}

void Chapter5::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, true , true , false },
		{ false, false, true , true , true , true  },
		{ true , false, true , true , true , true  },
		{ true , false, true , true , true , true  },
		{ true , false, true , true , true , true  },
		{ true , true , true , true , true , true  },
		{ false, false, false, false, false, true  }
	};
	
	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.345f, 0.16f });
	
	CreateBG("ChapterBG_005");
	M_CreateChapterUI(5);
	
	M_SpawnHero({ 0, 2 }, 23);
	
	M_SpawnSkeleton({ 0, 4 });

	M_SetIsThornChange(true);
	M_SpawnThorn({ 2, 2 }, EThornState::Down);
	M_SpawnThorn({ 3, 3 }, EThornState::Down);
	M_SpawnThorn({ 5, 3 }, EThornState::Down);
	M_SpawnThorn({ 0, 5 }, EThornState::Down);
	M_SpawnThorn({ 2, 5 }, EThornState::Down);
	M_SpawnThorn({ 5, 5 }, EThornState::Down);
	
	M_SpawnStone({ 4, 1 }, "Stone_011.png");
	M_SpawnStone({ 4, 2 }, "Stone_003.png");
	M_SpawnStone({ 2, 4 }, "Stone_007.png");
	M_SpawnStone({ 3, 4 }, "Stone_005.png");
	M_SpawnStone({ 4, 4 }, "Stone_009.png");
	M_SpawnStone({ 5, 4 }, "Stone_002.png");
	
	M_SpawnKeyComponent({ 5, 6 }, EKeyComponentType::Key);
	M_SpawnKeyComponent({ 3, 1 }, EKeyComponentType::LockBox);
	
	M_SpawnDemon({ 4, 0 }, "Zdrada");
	
	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter5::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("Zd", "Zd_Idle.png", Chap5_Script[0]);
	C_SpawnBooper();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * 0.021f }, {WinScale.X * 0.256f, WinScale.Y * 0.567f} });
	C_BooperTextSet(Chap5_Script[1]);
}

void Chapter5::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap5_Script[2]);
	C_MenubarTextSet(1, Chap5_Script[3]);
}

void Chapter5::SelectMenu()
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

void Chapter5::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap5_Script[4]);
}

void Chapter5::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap5_Script[5]);
}

void Chapter5::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * (-0.012f) }, { WinScale.X * 0.327f, WinScale.Y * 0.635f } });
	C_CharacterSetImage("Zd_Laugh.png");
	C_BooperTextSet(Chap5_Script[6]);
}

void Chapter5::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter6>("Chapter6");
	GEngine->ChangeLevel("Chapter6");
}

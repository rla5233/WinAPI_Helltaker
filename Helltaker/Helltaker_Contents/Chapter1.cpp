#include "Chapter1.h"

#include "ContentsHelper.h"

bool Chapter1::IsLoad = false;

const std::vector<const char*> Chap1_Script
{
	/* 0 Demon	  */ "�ǰ��� �Ǹ� �ǵ����ī",
	/* 1 Script 1 */ "���� �������� �ǵ����ī��� �մϴ�.\n������ ���͵帱���?",
	/* 2 MenuBar1 */ "�츮 ���� ���� �� �� �ְ���.", 
	/* 3 MenuBar2 */ "�۽�, ���� �� ������߰ڴµ�?",
	/* 4 Failed	  */ "������ ��Ƽ� �������� �� �������� �����Ѱž�?\n �޵� ũ�Ŷ�.", 
	/* 5 Bad End  */ "�ǵ����ī�� ����� ���� �վƱͷ� ����������\n �������ٿ� �ε巯�� �������� ���� ���� ���ȴ�.", 
	/* 6 Success  */ "�� ������ �����̿���.Ŀ�Ǹ� ���ð� �ͳ׿�.\n�ǰ��ؼ� ������ �������ھ��." 
};

Chapter1::Chapter1()
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_001.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Pand_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Pand_Flust.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "PandeMonica");

		IsLoad = true;
	}	
}

void Chapter1::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, true , true , false },
		{ false, true , true , true , true , true , false },
		{ false, true , true , true , true , false, false },
		{ true , true , false, false, false, false, false },
		{ true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation(6, 2);
	M_SetChapterEndPoint(5, 5);

	CreateBG("ChapterBG_001");
	M_CreateChapterUI(1);
	
	M_SpawnHero(5, 0, 23);
	M_SpawnSkeleton(3, 1);
	M_SpawnSkeleton(2, 2);
	M_SpawnSkeleton(4, 2);
	M_SpawnStone(1, 4, "Stone_002.png");
	M_SpawnStone(1, 5, "Stone_004.png");
	M_SpawnStone(4, 4, "Stone_009.png");
	M_SpawnStone(3, 5, "Stone_005.png");
	M_SpawnDemon(6, 5, "PandeMonica");

	M_StateChange(EChapterState::Idle);	

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter1::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("Pand", "Pand_Idle.png", Chap1_Script[0]);
	C_SpawnBooper();

	C_BooperTextSet(Chap1_Script[1]);
}

void Chapter1::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap1_Script[2]);
	C_MenubarTextSet(1, Chap1_Script[3]);
}

void Chapter1::SelectMenu()
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

void Chapter1::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap1_Script[4]);
}

void Chapter1::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap1_Script[5]);
}

void Chapter1::SuccessStart()
{
	CutSceneManager::SuccessStart();
	
	C_BooperTextSet(Chap1_Script[6]);
}
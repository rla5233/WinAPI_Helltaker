#include "Chapter1.h"

#include "ContentsHelper.h"


/////////// Test
#include "UI.h"

bool Chapter1::IsLoad = false;

const std::vector<const char*> Chap1_Script
{
	"�ǰ��� �Ǹ� �ǵ����ī", // Demon �̸�
	"���� �������� �ǵ����ī��� �մϴ�.\n������ ���͵帱���?", // ��� 1
	"�츮 ���� ���� �� �� �ְ���.", // MenuBar 1
	"�۽�, ���� �� ������߰ڴµ�?"// MenuBar 2
};

Chapter1::Chapter1()
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::BeginPlay()
{
	ChapterManager::BeginPlay();

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
	HellTakerManager::CutSceneStart();

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
	case 1:
		
		break;
	case 2:

		break;
	}
}

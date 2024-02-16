#include "Chapter1.h"

#include "ContentsHelper.h"

bool Chapter1::IsLoad = false;

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

	// 스테이지 생성
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

	StateChange(EChapterState::Idle);

	// 디버그용
	ShowLocationPoint();
}

void Chapter1::CutSecene(float _DeltaTime)
{
	

}

void Chapter1::CutSeceneStart()
{
	ChapterManager::CutSeceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnBooper();
	int a = 0;
}

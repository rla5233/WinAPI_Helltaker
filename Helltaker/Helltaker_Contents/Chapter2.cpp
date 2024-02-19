#include "Chapter2.h"

Chapter2::Chapter2()
{
}

Chapter2::~Chapter2()
{
}

void Chapter2::BeginPlay()
{
	ChapterManager::BeginPlay();
	ContentsHelper::LoadImg("BackGround", "ChapterBG_002.png");
	ContentsHelper::LoadFolder("Chapter\\Demon", "Modeus");
}

void Chapter2::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, true  , true  , true  , true , false, false },
		{ false, true  , false , true  , true , true , true  },
		{ true , true  , false , false , true , true , true  },
		{ true , true  , false , false , true , true , true  },
		{ true , true  , false , false , true , true , true  },
		{ false, false , false , false , true , true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation(6, 2);
	M_SetChapterEndPoint(4, 4);

	CreateBG("ChapterBG_002");
	M_CreateChapterUI(2);

	M_SpawnHero(0, 4, 24);
	M_SpawnSkeleton(1, 1);
	M_SpawnSkeleton(5, 4);
	M_SpawnSkeleton(6, 5);
	M_SpawnStone(4, 2, "Stone_003.png");
	M_SpawnStone(5, 2, "Stone_005.png");
	M_SpawnStone(6, 2, "Stone_007.png");
	M_SpawnThorn(1, 2, EThornState::Down);
	M_SpawnThorn(3, 1, EThornState::Down);
	M_SpawnThorn(4, 1, EThornState::Down);
	M_SpawnThorn(4, 2, EThornState::Down);
	M_SpawnThorn(5, 2, EThornState::Down);
	M_SpawnThorn(5, 3, EThornState::Down);
	M_SpawnDemon(4, 5, "Modeus");

	M_StateChange(EChapterState::Idle);

	// 디버그용
	ShowLocationPoint();
}

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

	CreateTileInfoVec(Map);
	SetChapterStartLocation(6, 2);
	SetChapterEndPoint(4, 4);

	CreateBG("ChapterBG_002");
	CreateChapterUI(2);

	SpawnHero(0, 4, 26);
	SpawnSkeleton(1, 1);
	SpawnSkeleton(5, 4);
	SpawnSkeleton(6, 5);
	SpawnStone(4, 2, "Stone_003.png");
	SpawnStone(5, 2, "Stone_005.png");
	SpawnStone(6, 2, "Stone_007.png");
	SpawnThorn(1, 2, EThornState::Down);
	SpawnThorn(3, 1, EThornState::Down);
	SpawnThorn(4, 1, EThornState::Down);
	SpawnThorn(4, 2, EThornState::Down);
	SpawnThorn(5, 2, EThornState::Down);
	SpawnThorn(5, 3, EThornState::Down);
	SpawnDemon(4, 5, "Modeus");

	// 디버그용
	ShowLocationPoint();
}

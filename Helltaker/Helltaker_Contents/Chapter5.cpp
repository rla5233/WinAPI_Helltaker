#include "Chapter5.h"

bool Chapter5::IsLoad = false;

const std::vector<const char*> Chap5_Script
{
	/* 0 Demon	  */ "상스러운 악마 즈드라다",
	/* 1 Script 1 */ "야, 하렘 꾸린다고 들었는데. 나도 낄래.",
	/* 2 MenuBar1 */ "잠깐만. 나중에 후회할 것 같은 기분인데.",
	/* 3 MenuBar2 */ "사실 하렘같은거 때려치웠어. 턴제 전략 게임이나 할 거야.",
	/* 4 Failed	  */ "어우 씨. 그 고통을 끝내줄게.",
	/* 5 Bad End  */ "갈비뼈 사이에 자루 깊숙이 박힌 칼을 끝으로 당신의 시야는 흐려졌다.",
	/* 6 Success  */ "안 됐지만 그래도 낄 거야. 막을 테면 막아 보던가."
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

		AddChapterSet("Chapter4");
		IsLoad = true;
	}
}

void Chapter5::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	//// 스테이지 생성
	//std::vector<std::vector<bool>> Map =
	//{
	//	{ false, false, false, true , true , false },
	//	{ false, false, true , true , true , true  },
	//	{ true , false, true , true , true , true  },
	//	{ true , false, true , true , true , true  },
	//	{ true , false, true , true , true , true  },
	//	{ true , true , true , true , true , true  },
	//	{ false, false, false, false, false, true  }
	//};
	//
	//M_CreateTileInfoVec(Map);
	//M_SetChapterStartLocation({ 0.292f, 0.255f });
	//
	//CreateBG("ChapterBG_005");
	//M_CreateChapterUI(5);
	//
	//M_SpawnHero({ 0, 2 }, 23);
	//
	//M_SetIsThornChange(false);
	//M_SpawnThorn({ 2, 1 }, EThornState::Up);
	//M_SpawnThorn({ 3, 1 }, EThornState::Up);
	//
	//M_SpawnStone({ 4, 0 }, "Stone_008.png");
	//M_SpawnStone({ 1, 1 }, "Stone_007.png");
	//M_SpawnStone({ 3, 1 }, "Stone_003.png");
	//M_SpawnStone({ 0, 2 }, "Stone_009.png");
	//M_SpawnStone({ 2, 2 }, "Stone_006.png");
	//M_SpawnStone({ 4, 2 }, "Stone_002.png");
	//M_SpawnStone({ 5, 2 }, "Stone_007.png");
	//M_SpawnStone({ 1, 3 }, "Stone_008.png");
	//M_SpawnStone({ 3, 3 }, "Stone_004.png");
	//M_SpawnStone({ 5, 3 }, "Stone_003.png");
	//M_SpawnStone({ 6, 3 }, "Stone_012.png");
	//M_SpawnStone({ 2, 4 }, "Stone_005.png");
	//M_SpawnStone({ 4, 4 }, "Stone_009.png");
	//
	//M_SpawnKeyComponent({ 2, 0 }, EKeyComponentType::Key);
	//M_SpawnKeyComponent({ 5, 1 }, EKeyComponentType::LockBox);
	//
	//M_SpawnDemon({ 7, 2 }, "Malina");
	//
	//M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter5::CutSceneStart()
{
}

void Chapter5::SelectStart()
{
}

void Chapter5::SelectMenu()
{
}

void Chapter5::BadEndStart()
{
}

void Chapter5::BadEndSetting()
{
}

void Chapter5::SuccessStart()
{
}

void Chapter5::ChangeChapter()
{
	int a = 0;
}

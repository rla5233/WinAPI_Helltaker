#include "Chapter6.h"

bool Chapter6::IsLoad = false;

const std::vector<const char*> Chap5_Script
{
	/* 0 Demon	  */ "호기심 많은 천사 아자젤",
	/* 1 Script 1 */ "하느님 맘소사! 살아있는 인간이 지옥에서 뭘 하고 있는 거죠?\n흔치 않은 일이네요.",
	/* 2 MenuBar1 */ "악마를 찾고 있어.",
	/* 3 MenuBar2 */ "천사를 찾고 있어.",
	/* 4 Failed	  */ "여기선 찾기 힘들거에요. 다행히 제가 좋은 곳을 알고 있죠.\n자, 손을 잡으세요.",
	/* 5 Bad End  */ "거짓말 때문에 천국에 가리라고 누가 예상이나 했을까.",
	/* 6 Bad End  */ "악마 하렘과는 영영 이별이지만.",
	/* 7 Success  */ "아, 그쪽도요? 혹시, 현대 죄악 관련 논문인가요? 아니면 악마학?\n같이 하는게 좋겠어요."
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
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
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

	M_SpawnDemon({ 5, 7 }, "Azazel");

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter6::CutSceneStart()
{
}

void Chapter6::SelectStart()
{
}

void Chapter6::SelectMenu()
{
}

void Chapter6::BadEndStart()
{
}

void Chapter6::BadEndSetting()
{
}

void Chapter6::SuccessStart()
{
}

void Chapter6::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	//CreateChapter<Chapter7>("Chapter7");
	//GEngine->ChangeLevel("Chapter7");
}
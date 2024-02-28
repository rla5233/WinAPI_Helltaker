#include "Chapter9.h"

bool Chapter9::IsLoad = false;

const std::vector<const char*> Chapter9::Chap9_Script
{
	/* 0 Demon	  */ "시큰둥한 악마 말리나",
	/* 1 Script 1 */ "대단하네, 또 골 빈 멍청이들이야...\n너같이 못생긴 놈은 처음인데, 지옥에서 뭘 하고 있어?",
	/* 2 MenuBar1 */ "너랑 같이 놀고 싶은데.",
	/* 3 MenuBar2 */ "기분 좋은데. 더 매도해 줘",
	/* 4 Failed	  */ "기가막히네 마조 변태나 또 보고.",
	/* 5 Bad End  */ "말리나가 팔을 휘두르자 작살 난 당신 목에서 피가 분수처럼\n터져 나왔다.",
	/* 6 Success  */ "뭐... 게임? 그래, 안 될 게 어디있어. 턴제 전략 게임이\n괜찮다면야."
};

Chapter9::Chapter9()
{
}

Chapter9::~Chapter9()
{
}

void Chapter9::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_009.png");

		AddChapterSet("Chapter9");
		IsLoad = true;
	}
}

void Chapter9::LevelStart(ULevel * _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, true, true , true , false, false, false },
		{ false, false, false, true, true , true , false, false, false },
		{ false, true , false, true, true , true , false, true , false },
		{ true , true , true , true, true , true , true , true , true  },
		{ true , true , true , true, true , true , true , true , true  },
		{ false, true , true , true, true , true , true , true , false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.267f, 0.3f });

	CreateBG("ChapterBG_009");
	M_CreateChapterUI(9);

	M_SpawnHero({ 1, 5 }, 33);

	M_SetIsThornChange(false);
	
	M_SpawnStone({ 3, 1 }, "Stone_009.png");
	M_SpawnStone({ 5, 1 }, "Stone_005.png");
	M_SpawnStone({ 1, 2 }, "Stone_005.png");
	M_SpawnStone({ 3, 2 }, "Stone_005.png");
	M_SpawnStone({ 0, 3 }, "Stone_005.png");
	M_SpawnStone({ 3, 3 }, "Stone_005.png");
	M_SpawnStone({ 4, 3 }, "Stone_005.png");
	M_SpawnStone({ 5, 3 }, "Stone_005.png");
	M_SpawnStone({ 1, 4 }, "Stone_005.png");
	M_SpawnStone({ 2, 4 }, "Stone_005.png");
	M_SpawnStone({ 3, 4 }, "Stone_005.png");
	M_SpawnStone({ 6, 4 }, "Stone_005.png");
	M_SpawnStone({ 7, 4 }, "Stone_005.png");
	M_SpawnStone({ 3, 5 }, "Stone_005.png");
	M_SpawnStone({ 6, 5 }, "Stone_005.png");
	
	//M_SpawnKeyComponent({ 1, 2 }, EKeyComponentType::Key);
	//M_SpawnKeyComponent({ 4, 1 }, EKeyComponentType::LockBox);
	//
	//FVector WinScale = ContentsHelper::GetWindowScale();
	//FVector Scale = { WinScale.X * 0.047f, WinScale.Y * 0.08f };
	//FVector Pos = { 0.0f, WinScale.Y * (-0.009f) };
	//M_SpawnDemon({ 3, 0 }, "Justice", { Pos, Scale });

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter9::CutSceneStart()
{}

void Chapter9::SelectStart()
{}

void Chapter9::SelectMenu()
{}

void Chapter9::BadEndStart()
{}

void Chapter9::BadEndSetting()
{}

void Chapter9::SuccessStart()
{}

void Chapter9::ChangeChapter()
{}
#include "Chapter4.h"

#include "Chapter5.h"

bool Chapter4::IsLoad = false;

const std::vector<const char*> Chap4_Script
{
	/* 0 Demon	  */ "시큰둥한 악마 말리나",
	/* 1 Script 1 */ "대단하네, 또 골 빈 멍청이들이야...\n너같이 못생긴 놈은 처음인데, 지옥에서 뭘 하고 있어?",
	/* 2 MenuBar1 */ "너랑 같이 놀고 싶은데.",
	/* 3 MenuBar2 */ "기분 좋은데. 더 매도해 줘",
	/* 4 Failed	  */ "기가막히네 마조 변태나 또 보고.",
	/* 5 Bad End  */ "말리나가 팔을 휘두르자 작살 난 당신 목에서 피가 분수처럼\n터져 나왔다.",
	/* 6 Success  */ "뭐... 게임? 그래, 안 될 게 어디있어. 턴제 전략 게임이\n괜찮다면야."
};

Chapter4::Chapter4()
{
}

Chapter4::~Chapter4()
{
}

void Chapter4::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_004.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mal_Puzzled.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Malina");

		AddChapterSet("Chapter4");
		IsLoad = true;
	}
}

void Chapter4::LevelStart(ULevel * _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ true , false, true , true , true , false, false, false },
		{ true , true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true , true  },
		{ true , true , true , true , true , true , true , true  },
		{ false, true , true , true , true , false, false, false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.292f, 0.255f });

	CreateBG("ChapterBG_004");
	M_CreateChapterUI(4);

	M_SpawnHero({ 0, 0 }, 23);

	M_SetIsThornChange(false);
	M_SpawnThorn({ 2, 1 }, EThornState::Up);
	M_SpawnThorn({ 3, 1 }, EThornState::Up);

	M_SpawnStone({ 4, 0 }, "Stone_008.png");
	M_SpawnStone({ 1, 1 }, "Stone_007.png");
	M_SpawnStone({ 3, 1 }, "Stone_003.png");
	M_SpawnStone({ 0, 2 }, "Stone_009.png");
	M_SpawnStone({ 2, 2 }, "Stone_006.png");
	M_SpawnStone({ 4, 2 }, "Stone_002.png");
	M_SpawnStone({ 5, 2 }, "Stone_007.png");
	M_SpawnStone({ 1, 3 }, "Stone_008.png");
	M_SpawnStone({ 3, 3 }, "Stone_004.png");
	M_SpawnStone({ 5, 3 }, "Stone_003.png");
	M_SpawnStone({ 6, 3 }, "Stone_012.png");
	M_SpawnStone({ 2, 4 }, "Stone_005.png");
	M_SpawnStone({ 4, 4 }, "Stone_009.png");

	M_SpawnKeyComponent({ 2, 0 }, EKeyComponentType::Key);
	M_SpawnKeyComponent({ 5, 1 }, EKeyComponentType::LockBox);

	M_SpawnDemon({ 7, 2 }, "Malina");

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter4::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("Mal", "Mal_Idle.png", Chap4_Script[0]);
	C_SpawnBooper();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * 0.05f}, {WinScale.X * 0.229f, WinScale.Y * 0.51f}});
	C_BooperTextSet(Chap4_Script[1]);
}

void Chapter4::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap4_Script[2]);
	C_MenubarTextSet(1, Chap4_Script[3]);
}

void Chapter4::SelectMenu()
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

void Chapter4::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap4_Script[4]);
}

void Chapter4::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap4_Script[5]);
}

void Chapter4::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * 0.017f }, { WinScale.X * 0.21f, WinScale.Y * 0.576f } });
	C_CharacterSetImage("Mal_Puzzled.png");
	C_BooperTextSet(Chap4_Script[6]);
}

void Chapter4::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter5>("Chapter5");
	GEngine->ChangeLevel("Chapter5");
}
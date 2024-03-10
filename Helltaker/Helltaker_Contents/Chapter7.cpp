#include "Chapter7.h"

#include "Character.h"
#include "Chapter8.h"

bool Chapter7::IsLoad = false;

const std::vector<const char*> Chapter7::Chap7_Script
{
	/* 0 Demon	  */ "끝내주는 악마 저스티스",
	/* 1 Script 1 */ "야, 저 퍼즐을 풀었어? 끝내주는데!",
	/* 2 MenuBar1 */ "푸느라 손 좀 갔지. 하렘에 들어올래?",
	/* 3 MenuBar2 */ "메뉴에서 그냥 건너뛰었어. 하렘에 들어올래?",
	/* 4 Success  */ "뭘 굳이 물어봐. 난 파티에 안 빠져.",
	/* 5 Success  */ "나라도 그랬겠다.\n당연히 가지. 많을수록 즐겁잖아?"
};

Chapter7::Chapter7()
{
}

Chapter7::~Chapter7()
{
}

void Chapter7::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_007.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Jus_Curious.png");

		AddChapterSet("Chapter7");
		IsLoad = true;
	}
}

void Chapter7::LevelStart(ULevel * _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, true, true , false },
		{ false, false, false, true, true , true  },
		{ true , true , false, true, true , true  },
		{ true , true , true , true, true , true  },
		{ true , false, true , true, true , true  },
		{ true , false, false, true, false, false },
		{ true , true , true , true, false, false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.345f, 0.162f });

	CreateBG("ChapterBG_007");
	M_CreateChapterUI(7);

	M_SpawnHero({ 5, 4 }, 32);

	M_SpawnSkeleton({ 0, 3 });
	M_SpawnSkeleton({ 3, 3 });
	M_SpawnSkeleton({ 2, 4 });

	M_SetIsThornChange(true);
	M_SpawnThorn({ 0, 5 }, EThornState::Up);
	M_SpawnThorn({ 3, 5 }, EThornState::Down);
	M_SpawnThorn({ 0, 6 }, EThornState::Down);
	M_SpawnThorn({ 1, 6 }, EThornState::Up);
	M_SpawnThorn({ 2, 6 }, EThornState::Down);
	M_SpawnThorn({ 3, 6 }, EThornState::Up);

	M_SpawnStone({ 3, 2 }, "Stone_009.png");
	M_SpawnStone({ 4, 2 }, "Stone_005.png");
	M_SpawnStone({ 5, 2 }, "Stone_007.png");
	M_SpawnStone({ 1, 3 }, "Stone_006.png");
	M_SpawnStone({ 4, 3 }, "Stone_002.png");

	M_SpawnKeyComponent({ 1, 2 }, EKeyComponentType::Key);
	M_SpawnKeyComponent({ 4, 1 }, EKeyComponentType::LockBox);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.047f, WinScale.Y * 0.08f };
	FVector Pos = { 0.0f, WinScale.Y * (-0.009f) };
	M_SpawnDemon({ 3, 0 }, "Justice", { Pos, Scale });

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter7::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");

	FVector Scale = { 0.228f, 0.567f };
	FVector Pos = { -0.005f, 0.02f };
	C_SpawnCharacter("Jus", "Jus_Curious.png", Chap7_Script[0], Pos, Scale);
	C_GetSceneCharacter()->StateChange(ECharacterState::Appear);

	C_SpawnBooper();
	C_BooperTextSet(Chap7_Script[1]);
}

void Chapter7::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap7_Script[2]);
	C_MenubarTextSet(1, Chap7_Script[3]);
}

void Chapter7::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		C_StateChange(ECutSceneState::Success);
		break;
	case 1:
		C_StateChange(ECutSceneState::Success);
		break;
	}
}

void Chapter7::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * 0.0f }, { WinScale.X * 0.22f, WinScale.Y * 0.612f } });
	C_CharacterSetImage("Jus_Idle.png");

	switch (C_GetFocusMenuIndex())
	{
	case 0:
		C_BooperTextSet(Chap7_Script[4]);
		break;
	case 1:
		C_BooperTextSet(Chap7_Script[5]); 
		break;
	}
	
}

void Chapter7::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter8>("Chapter8");
	GEngine->ChangeLevel("Chapter8");
}
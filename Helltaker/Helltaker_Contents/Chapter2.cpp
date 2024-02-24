#include "Chapter2.h"

#include "Chapter3.h"

bool Chapter2::IsLoad = false;

const std::vector<const char*> Chap2_Script
{
	/* 0 Demon	  */ "음란한 악마 모데우스",
	/* 1 Script 1 */ "너랑 나랑.지금 바로.",
	/* 2 MenuBar1 */ "좋아. 이의 없어.",
	/* 3 MenuBar2 */ "시간 없어.여자애들 모으기 바빠",
	/* 4 Failed	  */ "다들 그렇게 말하곤... 나중에 도망가려 하더라.\n 혹시 모르니 무릎을 부숴 놔야지.",
	/* 5 Bad End  */ "모데우스는 커다란 망치를 꺼냈다. 좋은 꼴은 못 볼 것 같다.",
	/* 6 Success  */ "악마 하렘? 불쌍한 멍청이... 악마들이 너를 갈가리 찢어 버릴 텐데,\n그걸 놓칠 수 없지."
};

Chapter2::Chapter2()
{
}

Chapter2::~Chapter2()
{
}

void Chapter2::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_002.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Mod_Close.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Modeus");

		AddChapterSet("Chapter2");
		IsLoad = true;
	}	
}

void Chapter2::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, true , true , true , true, false, false },
		{ false, true , false, true , true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ true , true , false, false, true, true , true  },
		{ false, false, false, false, true, true , true  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.318f, 0.208f });

	CreateBG("ChapterBG_002");
	M_CreateChapterUI(2);

	M_SpawnHero({ 0, 4 }, 24);

	M_SpawnSkeleton({ 1, 1 });
	M_SpawnSkeleton({ 5, 4 });
	M_SpawnSkeleton({ 6, 5 });

	M_SpawnStone({ 4, 2 }, "Stone_003.png");
	M_SpawnStone({ 5, 2 }, "Stone_005.png");
	M_SpawnStone({ 6, 2 }, "Stone_007.png");

	M_SetIsThornChange(false);
	M_SpawnThorn({ 1, 2 }, EThornState::Up);
	M_SpawnThorn({ 3, 1 }, EThornState::Up);
	M_SpawnThorn({ 4, 1 }, EThornState::Up);
	M_SpawnThorn({ 4, 2 }, EThornState::Up);
	M_SpawnThorn({ 5, 2 }, EThornState::Up);
	M_SpawnThorn({ 5, 3 }, EThornState::Up);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.048f, WinScale.Y * 0.08f };
	FVector Pos = { 0.0f, WinScale.Y * (-0.01f) };
	M_SpawnDemon({ 4, 5 }, "Modeus", { Pos, Scale });

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter2::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("Mod", "Mod_Idle.png", Chap2_Script[0]);
	C_SpawnBooper();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0, 0 }, { WinScale.X * 0.194f, WinScale.Y * 0.605f } });
	C_BooperTextSet(Chap2_Script[1]);
}

void Chapter2::SelectStart()
{
	CutSceneManager::SelectStart();

	C_MenubarTextSet(0, Chap2_Script[2]);
	C_MenubarTextSet(1, Chap2_Script[3]);
}

void Chapter2::SelectMenu()
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

void Chapter2::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap2_Script[4]);
}

void Chapter2::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap2_Script[5]);
}

void Chapter2::SuccessStart()
{
	CutSceneManager::SuccessStart();

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0, 0 }, { WinScale.X * 0.252f, WinScale.Y * 0.613f } });
	C_CharacterSetImage("Mod_Close.png");
	C_BooperTextSet(Chap2_Script[6]);
}

void Chapter2::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter3>("Chapter3");
	GEngine->ChangeLevel("Chapter3");
}
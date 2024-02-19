#include "Chapter2.h"

//#include "Chapter3.h"

bool Chapter2::IsLoad = false;

const std::vector<const char*> Chap2_Script
{
	/* 0 Demon	  */ "피곤한 악마 판데모니카",
	/* 1 Script 1 */ "지옥 고객센터의 판데모니카라고 합니다.\n무엇을 도와드릴까요?",
	/* 2 MenuBar1 */ "우리 집에 가면 알 수 있겠지.",
	/* 3 MenuBar2 */ "글쎄, 내가 널 도와줘야겠는데?",
	/* 4 Failed	  */ "지옥을 살아서 빠져나갈 수 있으리라 생각한거야?\n 꿈도 크셔라.",
	/* 5 Bad End  */ "판데모니카는 당신의 얼굴을 손아귀로 가져가더니\n 전문가다운 부드러운 동작으로 목을 꺽어 버렸다.",
	/* 6 Success  */ "참 달콤한 제안이에요.커피를 마시고 싶네요.\n피곤해서 정신을 못차리겠어요."
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

	M_SetIsThornChange(false);
	M_SpawnThorn(1, 2, EThornState::Up);
	M_SpawnThorn(3, 1, EThornState::Up);
	M_SpawnThorn(4, 1, EThornState::Up);
	M_SpawnThorn(4, 2, EThornState::Up);
	M_SpawnThorn(5, 2, EThornState::Up);
	M_SpawnThorn(5, 3, EThornState::Up);

	M_SpawnDemon(4, 5, "Modeus");

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

	C_BooperTextSet(Chap2_Script[6]);
}

void Chapter2::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	//CreateChapter<Chapter3>("Chapter3");
	//GEngine->ChangeLevel("Chapter3");
}
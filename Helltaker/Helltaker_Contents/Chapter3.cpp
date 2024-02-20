#include "Chapter3.h"

bool Chapter3::IsLoad = false;

const std::vector<const char*> Chap3_Script
{
	/* 0 Demon	  */ "세 쌍둥이 악마 케르베로스",
	/* 1 Script 1 */ "인간이야? 진짜 인간이야? 같이 데려가 줘.",
	/* 2 MenuBar1 */ "좋아. 이의 없어.",
	/* 3 MenuBar2 */ "너무 쉬워서 의심이 가는데...",
	/* 4 Failed	  */ "지옥문을 지나기 위해선 인간이 필요해서 그래.\n굳이 한조각일 필요는 없지만",
	/* 5 Bad End  */ "쌍둥이들이 미친 개마냥 당신에게 달려들었다.\n귀여운 강아지 소리와 함께 당신의 심장은 멈췄다.",
	/* 6 Success  */ "좋아, 드디어! 인간들을 타락시키러 가자!"
};

Chapter3::Chapter3()
{
}

Chapter3::~Chapter3()
{
}

void Chapter3::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_003.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Cer_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Cer_Happy.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Cerberus");

		AddChapterSet("Chapter3");
		IsLoad = true;
	}
}

void Chapter3::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, true , true , true , true , false  },
		{ false, false, false, false, false, false, true , false  },
		{ false, false, true , true , true , true , true , true   },
		{ false, false, true , false, true , false, true , true   },
		{ false, false, true , true , true , true , true , false  },
		{ true , false, true , false, true , false, true , false  },
		{ true , true , true , true , true , true , true , false  }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.29f, 0.16f });
	M_SetChapterEndPoint({ 6, 0 });

	CreateBG("ChapterBG_003");
	M_CreateChapterUI(3);
	
	M_SpawnHero({ 7, 2 }, 32);
	
	M_SpawnSkeleton({ 4, 4 });
	M_SpawnSkeleton({ 5, 6 });
	
	M_SetIsThornChange(false);
	M_SpawnThorn({ 3, 2 }, EThornState::Up);
	M_SpawnThorn({ 4, 2 }, EThornState::Up);
	M_SpawnThorn({ 2, 3 }, EThornState::Up);
	M_SpawnThorn({ 4, 3 }, EThornState::Up);
	M_SpawnThorn({ 5, 4 }, EThornState::Up);
	M_SpawnThorn({ 6, 4 }, EThornState::Up);
	M_SpawnThorn({ 4, 5 }, EThornState::Up);
	M_SpawnThorn({ 2, 5 }, EThornState::Up);

	M_SpawnDemon({ 3, 0 }, "Cerberus");
	M_SpawnDemon({ 4, 0 }, "Cerberus");
	M_SpawnDemon({ 5, 0 }, "Cerberus");
	
	M_StateChange(EChapterState::Idle);
	
#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter3::CutSceneStart()
{
}

void Chapter3::ChangeChapter()
{
}

void Chapter3::SelectStart()
{
}

void Chapter3::SelectMenu()
{
}

void Chapter3::BadEndStart()
{
}

void Chapter3::BadEndSetting()
{
}

void Chapter3::SuccessStart()
{
}

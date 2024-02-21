#include "Chapter8.h"

bool Chapter8::IsLoad = false;

const std::vector<const char*> Chap8_Script
{
	/* 0  Demon	     */ "지옥의 CEO 루시퍼",
	/* 1  Script 1   */ "이제야 만나네. 넌 시련들을 통과하며 가치를 증명했어.",
	/* 2  Script 2   */ "영혼을 바치면 아끼는 종으로 삼아 주마.",
	/* 3  MenuBar1_1 */ "네, 여왕님!",
	/* 4  MenuBar1_2 */ "사양헬게. 내 하렘에 들어와라.",
	/* 5  Failed1    */ "절절하고 어린 영혼이로군...",
	/* 6  Bad End1   */ "당신이 무릎을 꿇자 루시퍼는 당신의 이마에 입을 맞췄다.\n당신의 생명은 그대로 녹아내렸다.",
	/* 7  Script 3   */ "뭘 하려는 거지? 악마를 굴복시킬 수 있을 거라고 생각해?",
	/* 8  MenuBar2_1 */ "주인님이라고 불러라. 그리고 말을 꺼내기 전에 허락을 구해라.",
	/* 9  MenuBar2_2 */ "커피, 턴제 전략 게임과 초콜렛 팬케이크를 제공할 수 있지",
	/* 10 Failed2    */ "네 주제를 가르쳐 줘야겠구나.",
	/* 11 Bad End2   */ "루시퍼의 손짓에, 당신의 피는 모조리 식초로 변해버렸다.\n참으로 형언하기 어려운 느낌이다.",
	/* 12 Success1   */ "정말? 그게 다야? 여기까지 와 놓고선, 날 고작 팬케이크로\n 사려고?"
	/* 13 Success2   */ "내가 팬케이크를 좋아하니 운 좋은 줄 알아라."
	/* 14 Success3   */ "그럼 설득된 것 같네. 어쩌면 네 하렘이라는 게 재밌을 수도\n있겠어."
};

Chapter8::Chapter8()
{
}

Chapter8::~Chapter8()
{
}

void Chapter8::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_008.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Man_Skeleton.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Angry.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Happy.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Lucy");
		ContentsHelper::LoadFolder("Scene\\Characters", "Lu_Swirl");

		AddChapterSet("Chapter8");
		IsLoad = true;
	}
}

void Chapter8::LevelStart(ULevel * _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// 스테이지 생성
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, false, false, false, false, false },
		{ true , true , false, false, false, false, false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , false, true , true , true , false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , false, true , true , true , false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ false, true , false, true , true , true , false, true , false },
		{ false, true , true , true , true , true , true , true , false },
		{ false, true , false, true , true , true , false, true , false },
		{ false, true , true , true , true , true , true , true , false },
		{ false, false, false, true , true , true , false, false, false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.265f, 0.115f });

	CreateBG("ChapterBG_008");
	M_CreateChapterUI(8);

	M_SpawnHero({ 4, 11 }, 12);

	M_SpawnSkeleton({ 4, 2 });
	M_SpawnSkeleton({ 4, 3 });
	M_SpawnSkeleton({ 4, 4 });
	M_SpawnSkeleton({ 4, 5 });
	M_SpawnSkeleton({ 4, 6 });
	M_SpawnSkeleton({ 4, 7 });
	M_SpawnSkeleton({ 4, 8 });
	M_SpawnSkeleton({ 4, 9 });

	M_SetIsThornChange(false);

	M_SpawnDemon({ 4, 0 }, "Lucy");

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter8::CutSceneStart()
{}

void Chapter8::SelectStart()
{}

void Chapter8::SelectMenu()
{}

void Chapter8::BadEndStart()
{}

void Chapter8::BadEndSetting()
{}

void Chapter8::SuccessStart()
{}

void Chapter8::ChangeChapter()
{}
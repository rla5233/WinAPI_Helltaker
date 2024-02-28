#include "Chapter9.h"

#include "Character.h"

bool Chapter9::IsLoad = false;

const std::vector<const char*> Chapter9::Chap9_Script
{
	/* 0 Demon	  */ "???",
	/* 1 Script 1 */ "도망갈 수 있을 거라고 생각했느냐?",
	/* 2 Script 2 */ "그 짓거릴 해 놓고?",
	/* 3 Bad End  */ "피부에 닿은 사슬로부터 살을 에는 한기가 느껴졌다.\n뒤이어 뼛속까지 불태우는 불길이 느껴졌다.",
};

Chapter9::Chapter9()
{
}

Chapter9::~Chapter9()
{
}
// 수정 (컷신 렌더러 위치 조정)
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
	
	M_SpawnStone({ 3, 1 }, "Stone_004.png");
	M_SpawnStone({ 5, 1 }, "Stone_003.png");
	M_SpawnStone({ 1, 2 }, "Stone_005.png");
	M_SpawnStone({ 3, 2 }, "Stone_009.png");
	M_SpawnStone({ 0, 3 }, "Stone_006.png");
	M_SpawnStone({ 3, 3 }, "Stone_007.png");
	M_SpawnStone({ 4, 3 }, "Stone_008.png");
	M_SpawnStone({ 5, 3 }, "Stone_002.png");
	M_SpawnStone({ 1, 4 }, "Stone_004.png");
	M_SpawnStone({ 2, 4 }, "Stone_002.png");
	M_SpawnStone({ 3, 4 }, "Stone_003.png");
	M_SpawnStone({ 6, 4 }, "Stone_009.png");
	M_SpawnStone({ 7, 4 }, "Stone_007.png");
	M_SpawnStone({ 3, 5 }, "Stone_005.png");
	M_SpawnStone({ 6, 5 }, "Stone_006.png");
	
	M_SpawnKeyComponent({ 8, 3 }, EKeyComponentType::Key);
	M_SpawnKeyComponent({ 4, 1 }, EKeyComponentType::LockBox);

	EndPoint = { 4, 0 };

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter9::CutSceneCheck()
{
	if ((M_GetHeroNextLocationPoint() == EndPoint) 
	&& (M_GetHeroState() == EHeroState::Move))
	{
		M_StateChange(EChapterState::CutScene);
	}
}

void Chapter9::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	C_SpawnDialogue("DialogueBG_Hell.png");
	C_SpawnCharacter("???", "DefaultBG.png", Chap9_Script[0]);
	C_GetSceneCharacter()->GetImageRenderer()->ActiveOff();
	
	C_SpawnBooper();
	C_BooperTextSet(Chap9_Script[1]);
}

void Chapter9::EnterStart()
{
	EnterOrder = 0;
}

void Chapter9::Enter(float _DeltaTime)
{
	ResetCheck();

	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_StateChange(ECutSceneState::BadEnd);
	}
}

void Chapter9::BadEndStart()
{
	CutSceneManager::BadEndStart();

	C_BooperTextSet(Chap9_Script[2]);
}

void Chapter9::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	C_BooperTextSet(Chap9_Script[3]);
}

void Chapter9::ChangeChapter()
{
	int a = 0;
}
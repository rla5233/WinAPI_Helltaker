#include "Chapter6.h"

bool Chapter6::IsLoad = false;

const std::vector<const char*> Chap5_Script
{
	/* 0 Demon	  */ "ȣ��� ���� õ�� ������",
	/* 1 Script 1 */ "�ϴ��� ���һ�! ����ִ� �ΰ��� �������� �� �ϰ� �ִ� ����?\n��ġ ���� ���̳׿�.",
	/* 2 MenuBar1 */ "�Ǹ��� ã�� �־�.",
	/* 3 MenuBar2 */ "õ�縦 ã�� �־�.",
	/* 4 Failed	  */ "���⼱ ã�� ����ſ���. ������ ���� ���� ���� �˰� ����.\n��, ���� ��������.",
	/* 5 Bad End  */ "������ ������ õ���� ������� ���� �����̳� ������.",
	/* 6 Bad End  */ "�Ǹ� �Ϸ����� ���� �̺�������.",
	/* 7 Success  */ "��, ���ʵ���? Ȥ��, ���� �˾� ���� ���ΰ���? �ƴϸ� �Ǹ���?\n���� �ϴ°� ���ھ��."
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

	// �������� ����
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
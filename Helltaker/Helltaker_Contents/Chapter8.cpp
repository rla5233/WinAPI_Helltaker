#include "Chapter8.h"

bool Chapter8::IsLoad = false;

const std::vector<const char*> Chap8_Script
{
	/* 0  Demon	     */ "������ CEO �����",
	/* 1  Script 1   */ "������ ������. �� �÷õ��� ����ϸ� ��ġ�� �����߾�.",
	/* 2  Script 2   */ "��ȥ�� ��ġ�� �Ƴ��� ������ ��� �ָ�.",
	/* 3  MenuBar1_1 */ "��, ���մ�!",
	/* 4  MenuBar1_2 */ "������. �� �Ϸ��� ���Ͷ�.",
	/* 5  Failed1    */ "�����ϰ� � ��ȥ�̷α�...",
	/* 6  Bad End1   */ "����� ������ ���� ����۴� ����� �̸��� ���� �����.\n����� ������ �״�� ��Ƴ��ȴ�.",
	/* 7  Script 3   */ "�� �Ϸ��� ����? �Ǹ��� ������ų �� ���� �Ŷ�� ������?",
	/* 8  MenuBar2_1 */ "���δ��̶�� �ҷ���. �׸��� ���� ������ ���� ����� ���ض�.",
	/* 9  MenuBar2_2 */ "Ŀ��, ���� ���� ���Ӱ� ���ݷ� ������ũ�� ������ �� ����",
	/* 10 Failed2    */ "�� ������ ������ ��߰ڱ���.",
	/* 11 Bad End2   */ "������� ������, ����� �Ǵ� ������ ���ʷ� ���ع��ȴ�.\n������ �����ϱ� ����� �����̴�.",
	/* 12 Success1   */ "����? �װ� �پ�? ������� �� ����, �� ���� ������ũ��\n �����?"
	/* 13 Success2   */ "���� ������ũ�� �����ϴ� �� ���� �� �˾ƶ�."
	/* 14 Success3   */ "�׷� ����� �� ����. ��¼�� �� �Ϸ��̶�� �� ����� ����\n�ְھ�."
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

	// �������� ����
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
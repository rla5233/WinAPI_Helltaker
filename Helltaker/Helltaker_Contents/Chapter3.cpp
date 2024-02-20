#include "Chapter3.h"

bool Chapter3::IsLoad = false;

const std::vector<const char*> Chap3_Script
{
	/* 0 Demon	  */ "�� �ֵ��� �Ǹ� �ɸ����ν�",
	/* 1 Script 1 */ "�ΰ��̾�? ��¥ �ΰ��̾�? ���� ������ ��.",
	/* 2 MenuBar1 */ "����. ���� ����.",
	/* 3 MenuBar2 */ "�ʹ� ������ �ǽ��� ���µ�...",
	/* 4 Failed	  */ "�������� ������ ���ؼ� �ΰ��� �ʿ��ؼ� �׷�.\n���� �������� �ʿ�� ������",
	/* 5 Bad End  */ "�ֵ��̵��� ��ģ ������ ��ſ��� �޷������.\n�Ϳ��� ������ �Ҹ��� �Բ� ����� ������ �����.",
	/* 6 Success  */ "����, ����! �ΰ����� Ÿ����Ű�� ����!"
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

	// �������� ����
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

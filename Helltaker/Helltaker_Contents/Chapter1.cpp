#include "Chapter1.h"

#include "ContentsHelper.h"

Chapter1::Chapter1()
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::BeginPlay()
{
	ChapterManager::BeginPlay();
	ContentsHelper::LoadImg("BackGround", "ChapterBG_001.png");

	// ����� ��
	ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
	ContentsHelper::LoadImg("Debuging", "RedPoint.png");
}

void Chapter1::LevelStart(ULevel* _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, true , true , false },
		{ false, true , true , true , true , true , false },
		{ false, true , true , true , true , false, false },
		{ true , true , false, false, false, false, false },
		{ true , true , true , true , true , true , false },
		{ true , true , true , true , true , true , true  }
	};

	CreateChapterVec(Map);
	CreateHitActorVec();
	SetChapterStartLocation({ 6, 2 });

	CreateBG("ChapterBG_001");
	CreateChapterUI();
	
	SpawnHero(5, 0);
	SpawnSkeleton(3, 1);
	SpawnSkeleton(2, 2);
	SpawnSkeleton(4, 2);
	SpawnStone(1, 4, 2);
	SpawnStone(1, 5, 4);
	SpawnStone(4, 4, 9);	
	SpawnStone(3, 5, 5);
	SpawnDevil(6, 5, "PandeMonica");

	// ����׿�
	ShowLocationPoint();
}

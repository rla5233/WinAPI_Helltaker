#include "Chapter2.h"

Chapter2::Chapter2()
{
}

Chapter2::~Chapter2()
{
}

void Chapter2::BeginPlay()
{
	ChapterManager::BeginPlay();

	CreateBG("ChapterBG_002");
	CreateChapterUI();
}

#include "ChapterSin.h"

bool ChapterSin::IsLoad = false;
const std::vector<const char*> ChapSin_Script =
{
	/* 0 Demon	  */ "???",
	/* 1 Demon	  */ "���� ��Ұ� ������Ʈ",
	/* 2 Script 1 */ "��ġ õ ���� ���� �� ���� �����̴�. ������ �ұ���\n��׶���... ����Ƶ� ����� ���� ����ִ� �� ����.",
};

ChapterSin::ChapterSin()
{
}

ChapterSin::~ChapterSin()
{
}

void ChapterSin::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_002.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_LitHell.png");

		IsLoad = true;
	}
}

void ChapterSin::LevelStart(ULevel * _PrevLevel)
{

}

void ChapterSin::CutSceneStart()
{}

void ChapterSin::ChangeChapter()
{}

void ChapterSin::SelectStart()
{}

void ChapterSin::SelectMenu()
{}

void ChapterSin::BadEndStart()
{}

void ChapterSin::BadEndSetting()
{}

void ChapterSin::SuccessStart()
{}

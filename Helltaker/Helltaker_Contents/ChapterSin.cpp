#include "ChapterSin.h"

bool ChapterSin::IsLoad = false;
const std::vector<const char*> ChapSin_Script1 =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 2  Script 1  */ "��ġ õ ���� ���� �� ���� �����̴�. ������ �ұ���\n��׶���... ����Ƶ� ����� ���� ����ִ� �� ����.",
	/* 3  Script 2  */ "Ĩ���� �༮, ������ ã�Ҵ�!\n��	���� ���� �� ����.",
	/* 4  Script 3  */ "���� �Բ� ���� �ð��� ������ �� �Ŵ�.",
	/* 5  Script 4  */ "�˾��� ��迡 �õ��� �ɾ��! �÷��� ���� ���� ����!",
	/* 6  Script 5  */ "ħ���ھ�, �˾��� ��谡 ������ �����?",
	/* 7  Script 6  */ "�̸� �����ϰ� ��������!",
	/* 8  Script 7  */ "����� ������! �� �༮�� ����� �̹� ��������!",
	/* 9  Script 8  */ "�����϶�! ���� ��¥ �����̴�!",
	/* 10 Script 9  */ "�ʸ� �̰����� �̲����� �͵��� �罽�� �Ǿ� �ʸ� �ְ���.",
	/* 11 Script 10 */ "���� ����, Ž��, �׸��� ����. �� ������ ������ �Ŵ�.",


};

const std::vector<const char*> ChapSin_Script2 =
{
	/* 0 Demon	  */ "�� �ֵ��� �Ǹ� �ɸ����ν�",
	/* 1 Demon	  */ "�ǰ��� �Ǹ� �ǵ����ī",
	/* 2 Demon	  */ "������ CEO �����",
	/* 3 Script 1 */ "�ȵ�, �������� ��! �츱 ������ ��������!",
	/* 4 Script 2 */ "�׸��� Ŀ�ǵ� Ÿ �ּž���.",
	/* 5 Script 3 */ "�̷�, ������Ʈ. �� �༮�� �𸣰� �ְ�����, �� �ž�. �׳�\n������ �� ���� ����?",
	/* 6 Script 4 */ "�׸�! ���� ��Ұ�, ��� ������ ���� ���Ѵ�!",

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

#include "Chapter9.h"

bool Chapter9::IsLoad = false;

const std::vector<const char*> Chap9_Script
{
	/* 0 Demon	  */ "��ū���� �Ǹ� ������",
	/* 1 Script 1 */ "����ϳ�, �� �� �� ��û�̵��̾�...\n�ʰ��� ������ ���� ó���ε�, �������� �� �ϰ� �־�?",
	/* 2 MenuBar1 */ "�ʶ� ���� ��� ������.",
	/* 3 MenuBar2 */ "��� ������. �� �ŵ��� ��",
	/* 4 Failed	  */ "�Ⱑ������ ���� ���³� �� ����.",
	/* 5 Bad End  */ "�������� ���� �ֵθ��� �ۻ� �� ��� �񿡼� �ǰ� �м�ó��\n���� ���Դ�.",
	/* 6 Success  */ "��... ����? �׷�, �� �� �� ����־�. ���� ���� ������\n�����ٸ��."
};

Chapter9::Chapter9()
{
}

Chapter9::~Chapter9()
{
}

void Chapter9::BeginPlay()
{}

void Chapter9::LevelStart(ULevel * _PrevLevel)
{}

void Chapter9::CutSceneStart()
{}

void Chapter9::SelectStart()
{}

void Chapter9::SelectMenu()
{}

void Chapter9::BadEndStart()
{}

void Chapter9::BadEndSetting()
{}

void Chapter9::SuccessStart()
{}

void Chapter9::ChangeChapter()
{}
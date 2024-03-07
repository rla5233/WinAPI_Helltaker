#include "SinOpening.h"

#include "Character.h"
#include "Scene.h"

bool SinOpening::IsLoad = false;
const std::vector<const char*> SinOpening::SinOpening_Script =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "���� ��Ұ� ������Ʈ",
	/* 2  Script 1  */ "��ġ õ ���� ���� �� ���� �����̴�. ������ �ұ���\n��׶���... ����Ƶ� ����� ���� ����ִ� �� ����.",
	/* 3  Script 2  */ "Ĩ���� �༮, ������ ã�Ҵ�!\n�� ���� ���� �� ����.",
	/* 4  Script 3  */ "���� �Բ� ���� �ð��� ������ �� �Ŵ�.",
	/* 5  Script 4  */ "�˾��� ��迡 �õ��� �ɾ��! �÷��� ���� ���� ����!"
};

SinOpening::SinOpening()
{
}

SinOpening::~SinOpening()
{

}

void SinOpening::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{



		IsLoad = false;
	}
}

void SinOpening::LevelStart(ULevel * _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);
}

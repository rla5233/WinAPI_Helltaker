#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// ���ӽ���
void Helltaker_ContentsCore::Start()
{
	//MainWindow.SetTitle();
	//MainWindow.SetScale();

	CreateLevel<UTitleLevel>("Title");

	// �̶��Ǹ� �̹� ������ â�� ��������ִ� �����ϰŶ�� 
	int a = 0;
}

void Helltaker_ContentsCore::Update()
{
	int a = 0;
}

void Helltaker_ContentsCore::End()
{
	int a = 0;
}
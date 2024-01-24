#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// 게임시작
void Helltaker_ContentsCore::Start()
{
	//MainWindow.SetTitle();
	//MainWindow.SetScale();

	CreateLevel<UTitleLevel>("Title");

	// 이때되면 이미 윈도우 창은 만들어져있는 상태일거라고 
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
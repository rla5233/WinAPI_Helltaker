#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// 게임시작
void Helltaker_ContentsCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void Helltaker_ContentsCore::Tick(float _DeltaTime)
{
	int a = 0;
}

void Helltaker_ContentsCore::End()
{
	int a = 0;
}
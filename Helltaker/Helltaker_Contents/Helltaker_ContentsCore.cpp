#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// ���ӽ���
void Helltaker_ContentsCore::BeginPlay()
{
	SetFrame(165);

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void Helltaker_ContentsCore::Tick(float _DeltaTime)
{

}

void Helltaker_ContentsCore::End()
{

}
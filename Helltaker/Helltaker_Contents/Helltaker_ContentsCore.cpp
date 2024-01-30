#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"

#include "PlayStage1.h"

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// 게임시작
void Helltaker_ContentsCore::BeginPlay()
{
	SetFrame(165);

	//CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UPlayLevel>("PlayLevel");
	CreateLevel<UPlayStage1>("PlayStage1");

	ChangeLevel("PlayStage1");
}

void Helltaker_ContentsCore::Tick(float _DeltaTime)
{
	
}

void Helltaker_ContentsCore::End()
{

}
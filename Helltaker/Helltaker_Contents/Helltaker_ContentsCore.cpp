#include "Helltaker_ContentsCore.h"

#include "Title.h"
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
	MainWindow.SetWindowScale({ 1280, 720 });
	UEngineCore::BeginPlay();

	SetFrame(165);

	CreateLevel<Title>("Title");
	ChangeLevel("Title");

	//CreateLevel<UPlayStage1>("PlayStage1");
	//ChangeLevel("PlayStage1");
}

void Helltaker_ContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}

void Helltaker_ContentsCore::End()
{
	UEngineCore::End();
}
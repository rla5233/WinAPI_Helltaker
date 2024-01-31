#include "Helltaker_ContentsCore.h"
#include "TitleLevel.h"

#include "PlayStage1.h"
#include <EnginePlatform/WindowImage.h>

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// ���ӽ���
void Helltaker_ContentsCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 1280, 720 });

	UEngineCore::BeginPlay();

	SetFrame(165);

	//CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UPlayLevel>("PlayLevel");
	CreateLevel<UPlayStage1>("PlayStage1");

	ChangeLevel("PlayStage1");
}

void Helltaker_ContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}

void Helltaker_ContentsCore::End()
{
	UEngineCore::End();
}
#include "Helltaker_ContentsCore.h"

#include "Opening.h"

#include <EnginePlatform/EngineWindow.h>


// Test
#include "Chapter1.h"
#include "MainMenu.h"


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

	//CreateLevel<Opening>("Opening");
	//ChangeLevel("Opening");

	//CreateLevel<MainMenu>("MainMenu");
	//ChangeLevel("MainMenu");

	CreateLevel<Chapter1>("Chapter1");
	ChangeLevel("Chapter1");
}

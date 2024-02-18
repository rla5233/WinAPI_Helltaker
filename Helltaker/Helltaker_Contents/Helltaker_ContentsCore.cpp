#include "Helltaker_ContentsCore.h"

#include "Opening.h"

#include <EnginePlatform/EngineWindow.h>


// Test
#include "Chapter1.h"
#include "Chapter2.h"
#include "MainMenu.h"


Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// ���ӽ���
void Helltaker_ContentsCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 1920, 1080 });
	//MainWindow.SetWindowScale({ 1280, 720 });
	UEngineCore::BeginPlay();

	SetFrame(60);

	CreateLevel<Opening>("Opening");
	ChangeLevel("Opening");

	//CreateLevel<MainMenu>("MainMenu");
	//ChangeLevel("MainMenu");

	CreateLevel<Chapter1>("Chapter1");
	ChangeLevel("Chapter1");

	//CreateLevel<Chapter2>("Chapter2");
	//ChangeLevel("Chapter2");
}

#include "Helltaker_ContentsCore.h"

#include "Opening.h"

// Test
#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"
#include "Chapter5.h"
#include "Chapter6.h"
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
	MainWindow.SetWindowScale({ 1920, 1080 });
	//MainWindow.SetWindowScale({ 1280, 720 });
	UEngineCore::BeginPlay();

	SetFrame(60);

    //CreateLevel<Opening>("Opening");
    //ChangeLevel("Opening");

	//CreateLevel<MainMenu>("MainMenu");
	//ChangeLevel("MainMenu");

	//CreateLevel<Chapter1>("Chapter1");
	//ChangeLevel("Chapter1");

	//CreateLevel<Chapter2>("Chapter2");
	//ChangeLevel("Chapter2");

	//CreateLevel<Chapter3>("Chapter3");
	//ChangeLevel("Chapter3");

	//CreateLevel<Chapter4>("Chapter4");
	//ChangeLevel("Chapter4");

    //CreateLevel<Chapter5>("Chapter5");
    //ChangeLevel("Chapter5");

	CreateLevel<Chapter6>("Chapter6");
	ChangeLevel("Chapter6");
}

#include "Helltaker_ContentsCore.h"

#include "Opening.h"
#include "Chapter1.h"


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

	CreateLevel<Opening>("Opening");
	ChangeLevel("Opening");

	//CreateLevel<Chapter1>("Chapter1");
	//ChangeLevel("Chapter1");
}
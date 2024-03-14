#include "Helltaker_ContentsCore.h"

#include "Opening.h"

#include <time.h>

// Test
#include "MainMenu.h"
#include "Chapter1.h"
#include "Chapter2.h"
#include "Chapter3.h"
#include "Chapter4.h"
#include "Chapter5.h"
#include "Chapter6.h"
#include "Chapter7.h"
#include "Chapter8.h"
#include "Chapter9.h"
#include "SinOpening.h"
#include "SinChapter1.h"
#include "SinChapter2.h"
#include "SinChapter3.h"
#include "SinChapter4.h"
#include "Epilogue.h"
#include "EpilogueOpening.h"

// 수정 (스크립트 문자 재확인), (매개 변수 안쓰는거 정리)
Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

// 게임시작
void Helltaker_ContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();
	MainWindow.SetClearColor(Color8Bit(2, 2, 27, 255));
	MainWindow.SetWindowScale({ 1920, 1080 });
	SetFrame(60);

    CreateLevel<Opening>("Opening");
    ChangeLevel("Opening");

	CreateLevel<MainMenu>("MainMenu");
	ChangeLevel("MainMenu");

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

	//CreateLevel<Chapter6>("Chapter6");
	//ChangeLevel("Chapter6");

	//CreateLevel<Chapter7>("Chapter7");
	//ChangeLevel("Chapter7");

	//CreateLevel<Chapter8>("Chapter8");
	//ChangeLevel("Chapter8");
		
	//CreateLevel<Chapter9>("Chapter9");
	//ChangeLevel("Chapter9");

	CreateLevel<SinOpening>("SinOpening");
	ChangeLevel("SinOpening");
	
	CreateLevel<SinChapter1>("SinChapter1");
    ChangeLevel("SinChapter1");
	
	//CreateLevel<SinChapter2>("SinChapter2");
	//ChangeLevel("SinChapter2");
	
	//CreateLevel<SinChapter3>("SinChapter3");
    //ChangeLevel("SinChapter3");
	
	//CreateLevel<SinChapter4>("SinChapter4");
	//ChangeLevel("SinChapter4");
	
	//CreateLevel<EpilogueOpening>("EpilogueOpening");
	//ChangeLevel("EpilogueOpening");
	
	//CreateLevel<Epilogue>("Epilogue");
	//ChangeLevel("Epilogue");
}

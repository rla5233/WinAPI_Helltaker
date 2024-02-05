#include "Title.h"

#include "ContentsEnum.h"
#include "ContentsHelper.h"
#include "BackGround.h"

#include <EnginePlatform/EngineWindow.h>

Title::Title()
{
}

Title::~Title()
{
}

void Title::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* OpeningBG = SpawnActor<BackGround>();
	OpeningBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	OpeningBG->LoadRenderImage("Opening", "Opening.png");
	OpeningBG->SetRenderImage("Opening.png", RenderOrder::BackGround);

	BackGround* UnityLogo = SpawnActor<BackGround>();
	OpeningBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	OpeningBG->LoadRenderImage("Opening", "UnityLogo.png");
	OpeningBG->SetRenderImage("Opening.png", RenderOrder::BackGround);
}

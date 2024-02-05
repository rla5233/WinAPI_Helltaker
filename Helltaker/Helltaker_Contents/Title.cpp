#include "Title.h"

#include "ContentsEnum.h"
#include "ContentsHelper.h"
#include "BackGround.h"
#include "Dialogue.h"

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

	Dialogue* UnityLogo = SpawnActor<Dialogue>();
	UnityLogo->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
}

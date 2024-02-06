#include "Opening.h"

#include "ContentsEnum.h"
#include "ContentsHelper.h"
#include "BackGround.h"
#include "Dialogue.h"

#include <EnginePlatform/EngineWindow.h>

Opening::Opening()
{
}

Opening::~Opening()
{
}

void Opening::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* OpeningBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	OpeningBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	OpeningBG->SetName("OpeningBG.png");
	OpeningBG->LoadBG();
	OpeningBG->SetBG();

	Dialogue* UnityLogo = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	UnityLogo->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	UnityLogo->SetName("UnityLogo.png");
	UnityLogo->SetScale({ WinScale.X / 5, WinScale.Y / 5 });
	UnityLogo->LoadImgDialogue();
	UnityLogo->SetImgDialogue();
}

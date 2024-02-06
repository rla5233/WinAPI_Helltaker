#include "MainMenu.h"

#include "ContentsHelper.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include "Dialogue.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageRenderer.h>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* DefaultBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	DefaultBG->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2 });
	DefaultBG->SetName("DefaultBG.png");
	DefaultBG->LoadBG();
	DefaultBG->SetBG();

	Dialogue* MainMenuDialogue = SpawnActor<Dialogue>(static_cast<int>(UpdateOrder::Dialogue));
	MainMenuDialogue->SetActorLocation({ WinScale.X / 2, WinScale.Y / 2.45f });
	MainMenuDialogue->SetName("MainMenuDialogue_001.png");
	MainMenuDialogue->LoadImgDialogue();
	MainMenuDialogue->SetImgDialogue(true);
}

void MainMenu::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

}

void MainMenu::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	


}
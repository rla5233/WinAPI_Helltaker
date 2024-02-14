#pragma once

#include "ContentsHelper.h"

#include <vector>
#include <EngineCore/Level.h>

class Character;
class UI;

// Ό³Έν :
class MainMenu : public ULevel
{
public:
	// constructor destructor
	MainMenu();
	~MainMenu();

	// delete Function
	MainMenu(const MainMenu& _Other) = delete;
	MainMenu(MainMenu&& _Other) noexcept = delete;
	MainMenu& operator=(const MainMenu& _Other) = delete;
	MainMenu& operator=(MainMenu&& _Other) noexcept = delete;



	void Begin(float _DeltaTime);
	void BeginStart();

	void Enter(float _DeltaTime);
	void EnterStart();

	void SelectMenu(float _DeltaTime);
	void SelectMenuInit();
	void SelectMenuStart();

	void EnterChapter(float _DeltaTime);
	void EnterChapterStart();

	void Exit(float _DeltaTime);

	void StateUpdate(float _DeltaTime);
	void StateChange(EMainMenuState _State);	
	
	void SetFocusMenuIndex(int _Index)
	{
		FocusMenuIndex = _Index;

		if (FocusMenuIndex < 0)
		{
			FocusMenuIndex = MenuBarCount - 1;
		}

		if (FocusMenuIndex >= MenuBarCount)
		{
			FocusMenuIndex = 0;
		}
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	std::list<AActor*> AllActors;
	
	Character* Beel = nullptr;	
	
	UI* Booper = nullptr;
	std::vector<UI*> MenuBarVec;
	
	int MenuBarCount = 3;
	int FocusMenuIndex = 0;

	bool IsSelectMenuInit = false;
	
	int SelectChapterNum = -1;
	EMainMenuState State = EMainMenuState::None;
};

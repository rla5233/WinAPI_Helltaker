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

	void StateUpdate(float _DeltaTime);
	void StateChange(EMainMenuState _State);

	void Begin(float _DeltaTime);

	void Enter(float _DeltaTime);
	void EnterInit();

	void SelectMenu(float _DeltaTime);
	void SelectMenuInit();
	void SelectMenuStart(float _DeltaTime);

	void SetFocusMenuIndex(int _Index)
	{
		FocusMenuIndex = _Index;

		if (FocusMenuIndex < 0)
		{
			FocusMenuIndex = 0;
		}

		if (FocusMenuIndex >= MenuBarCount)
		{
			FocusMenuIndex = MenuBarCount - 1;
		}
	}

	int GetFocusMenuIndex() const
	{
		return FocusMenuIndex;
	}


	void Exit(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	Character* Beel = nullptr;
	
	UI* Booper = nullptr;
	std::vector<UI*> MenuBarVec;
	int MenuBarCount = 3;
	int FocusMenuIndex = 0;

	bool IsEnterInit = false;
	bool IsSelectMenuInit = false;
	
	EMainMenuState State = EMainMenuState::None;
};

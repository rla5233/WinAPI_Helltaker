#pragma once

#include "ContentsHelper.h"

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
	void Exit(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	Character* Beel = nullptr;
	UI* Booper = nullptr;

	EMainMenuState State = EMainMenuState::None;
	bool IsEnterInit = false;
};

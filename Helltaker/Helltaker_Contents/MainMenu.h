#pragma once

#include "CutSceneManager.h"

// ���� :
class MainMenu : public CutSceneManager
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

	void StateChange(EMainMenuState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void SelectStart() override;
	void Select() override;
	void SelectMenu() override;

private:
	void StateUpdate(float _DeltaTime);

	void BeginStart();
	void Begin();

	void EnterStart();
	void Enter();

	void NewGameStart();
	void NewGame();
	void NewGameOrder1();
	void NewGameOrder2();
	void NewGameLastOrder();

	void EnterChapter();
	void EnterChapterStart();

	void Exit();
	void ExitStart();

private:
	int NewGameOrder = -1;
	int SelectChapterNum = -1;
	
	EMainMenuState State = EMainMenuState::None;

	static const std::vector<const char*> MainMenu_Script;
	static bool IsLoad;
};

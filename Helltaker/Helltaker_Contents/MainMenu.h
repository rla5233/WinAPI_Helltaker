#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
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
	void SelectMenu() override;

private:
	void StateUpdate(float _DeltaTime);

	void BeginStart();
	void Begin(float _DeltaTime);

	void Select(float _DeltaTime);

	void EnterStart();
	void Enter(float _DeltaTime);

	void NewGameStart();
	void NewGame(float _DeltaTime);
	void NewGameOrder1();
	void NewGameOrder2();
	void NewGameLastOrder();

	void EnterChapter();
	void EnterChapterStart();

	void Exit(float _DeltaTime);
	void ExitStart();

	void DialogueMoveUpdate(float _DeltaTime);

private:
	int NewGameOrder = -1;
	int SelectChapterNum = -1;
	float DialogueMoveSum = 0.0f;
	
	EMainMenuState State = EMainMenuState::None;

	static const std::vector<const char*> MainMenu_Script;
	static bool IsLoad;
};

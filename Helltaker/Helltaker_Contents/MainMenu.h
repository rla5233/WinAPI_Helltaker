#pragma once

#include "CutSceneManager.h"

#include <EnginePlatform/EngineSound.h>

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
	void SelectMenu() override;

private:
	void BeginStart();
	void Begin(float _DeltaTime);

	void Select(float _DeltaTime);
	void ReturnSelect();

	void EnterStart();
	void Enter(float _DeltaTime);

	void NewGameStart();
	void NewGame(float _DeltaTime);
	void NewGameOrder1();
	void NewGameOrder2();
	void NewGameLastOrder();

	void SelectChapterStart();
	void SelectChapter(float _DeltaTime);
	void SelectChapterMenu();

	void EnterChapterStart();
	void EnterChapter();

	void ReturnStart();
	void Return(float _DeltaTime);
	void Return1();
	void Return2();
	bool SetReturn = false;

	void ExitStart();
	void Exit(float _DeltaTime);

	void SpawnSC_MenuBar(int _IndexCount);
	void SC_MenuBarOn();
	void SC_MenuBarOff();

	void FocusSC_MenuBarCheck();
	void AutoSC_SelectMenuImage();
	void AutoSC_UnSelectMenuImage();
	void SetFocusSC_MenuIndex(int _Index);

	void DialogueMoveUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	int OrderCount = -1;
	int SelectChapterNum = -1;
	float DialogueMoveSum = 0.0f;
	
	int SC_MenuCount = -1;
	int FocusSC_MenuIndex = -1;
	std::vector<UI*> SC_MenuBar;
	
	UEngineSoundPlayer MainMenuBGMPlayer;

	EMainMenuState State = EMainMenuState::None;

	static bool ReturnMainMenu;
	static const std::vector<const char*> MainMenu_Script;
	static bool IsLoad;
};

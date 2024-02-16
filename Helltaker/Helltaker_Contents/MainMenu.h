#pragma once

#include "ContentsHelper.h"

#include <vector>
#include <EngineCore/Level.h>

class Character;
class Scene;
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

	void CutScene(float _DeltaTime);
	void CutSceneStart();

	void EnterChapter(float _DeltaTime);
	void EnterChapterStart();

	void Exit(float _DeltaTime);

	void CreateTransition();
	void SpawnDialogue();
	void SpawnBooper();

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

	void StateUpdate(float _DeltaTime);
	void StateChange(EMainMenuState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	std::list<AActor*> AllActors;
	
	const float TransitionInter = 0.0435f;
	Scene* TransitionActor = nullptr;
	Character* Beel = nullptr;	
	Scene* Dialogue = nullptr;
	Scene* SceneActor = nullptr;
	int SceneIndex = -1;
	bool SceneInput = false;
	
	UI* Booper = nullptr;
	std::vector<UI*> MenuBarVec;
	
	const int MenuBarCount = 3;
	int FocusMenuIndex = -1;

	bool IsSelectMenuInit = false;
	
	int SelectChapterNum = -1;
	EMainMenuState State = EMainMenuState::None;
};

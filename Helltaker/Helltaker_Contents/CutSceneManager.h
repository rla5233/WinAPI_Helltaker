#pragma once

#include "ChapterManager.h"

// Ό³Έν :
class CutSceneManager : public ChapterManager
{
public:
	// constructor destructor
	CutSceneManager();
	~CutSceneManager();

	// delete Function
	CutSceneManager(const CutSceneManager& _Other) = delete;
	CutSceneManager(CutSceneManager&& _Other) noexcept = delete;
	CutSceneManager& operator=(const CutSceneManager& _Other) = delete;
	CutSceneManager& operator=(CutSceneManager&& _Other) noexcept = delete;

	// CutScene
	void C_SpawnDialogue(std::string_view _Name);
	void C_SpawnCharacter(std::string_view _Name, std::string_view _ImgName, std::string_view _Text);
	void C_SpawnBooper();
	void C_SpawnMenubar();

	void C_BooperTextSet(std::string_view _Text);


protected:
	virtual void Tick(float _DeltaTime) override;

	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart() override;

private:
	void C_StateUpdate(float _DeltaTime);
	void C_StateChange(ECutScenePhase _State);

	void EnterChooseMenuCheck();
	void SetFocusMenuIndex(int _Index);
	void SelectMenuBar();


private:
	std::list<AActor*> AllCutSceneActors;

	Character* C_Character = nullptr;
	UI* C_Booper = nullptr;
	std::vector<UI*> MenuBar;
	int MenuBarCount = 2;
	int FocusMenuIndex = -1;
	
	ECutScenePhase State = ECutScenePhase::None;
};

using HellTakerManager = CutSceneManager;
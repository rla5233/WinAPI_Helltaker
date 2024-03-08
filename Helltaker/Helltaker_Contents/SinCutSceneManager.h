#pragma once

#include "SinChapterManager.h"

class Sin_Dialogue;
class Character;
class Sin_Judge;
class UI;

// Ό³Έν :
class SinCutSceneManager : public SinChapterManager
{
public:
	// constructor destructor
	SinCutSceneManager();
	~SinCutSceneManager();
	
	// delete Function
	SinCutSceneManager(const SinCutSceneManager& _Other) = delete;
	SinCutSceneManager(SinCutSceneManager&& _Other) noexcept = delete;
	SinCutSceneManager& operator=(const SinCutSceneManager& _Other) = delete;
	SinCutSceneManager& operator=(SinCutSceneManager&& _Other) noexcept = delete;

	void C_CreateSceneBG();

	void C_SpawnDialogue(int _PosType);
	void C_SpawnJudge(
		std::string_view _ImgName, 
		std::string_view _Text = " ", 
		const FVector& _Pos = { 0.0f , 0.0f },
		const FVector& _Scale = { 0.0f , 0.0f });
	void C_SpawnBooper();
	void C_SpawnMenubar(FVector _Pos = { 0.5f, 0.86f }, int _MenuBarCount = 2);

	void C_BooperTextSet(std::string_view _Text);
	void C_BooperSetTextPosition(int _LineCount);

	Sin_Dialogue* C_GetDialogue() const
	{
		return Dialogue;
	}

	Sin_Judge* C_GetJudge() const
	{
		return Judge;
	}

	UI* C_GetBooper() const
	{
		return Booper;
	}

	void C_StateChange(ESinSceneState _State);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart() override;

	virtual void EnterStart() {};
	virtual void Enter(float _DeltaTime);
	
	virtual void EndStart() {};

	virtual void SelectMenu() {};

	void ResetCheck() override;

private:
	void End(float _DeltaTime);

	bool FocusMenuBarCheck();
	void SetFocusMenuIndex(int _Index);

	void StateUpdate(float _DeltaTime);

private:
	// Manager
	std::list<AActor*> AllCutSceneActors;

	Sin_Judge* Judge = nullptr;
	Sin_Dialogue* Dialogue = nullptr;
	UI* Booper = nullptr;

	std::vector<UI*> MenuBar;
	int MenuBarCount = -1;
	int FocusMenuIndex = -1;
	static const FVector FocusMenuScale;
	static const FVector UnFocusMenuScale;
	
	ESinSceneState State = ESinSceneState::None;
};

using SinManager = SinCutSceneManager;
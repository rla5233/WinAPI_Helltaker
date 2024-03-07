#pragma once

#include "SinChapterManager.h"

class Sin_Dialogue;
class Character;
class UI;

// 설명 :
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
	// 수정 (캐릭터 스폰 추가)
	void C_SpawnBooper();
	void C_SpawnMenubar(FVector _Pos = { 0.5f, 0.86f }, int _MenuBarCount = 2);

	void C_BooperTextSet(std::string_view _Text);
	void C_BooperSetTextPosition(int _LineCount);

	Sin_Dialogue* GetDialogue() const
	{
		return Dialogue;
	}

	UI* GetBooper() const
	{
		return Booper;
	}

	void C_StateChange(ESinSceneState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CutSceneStart() override;

	virtual void EnterStart() {};
	virtual void Enter(float _DeltaTime);

	virtual void SelectMenu() {};

	void ResetCheck() override;

private:
	bool FocusMenuBarCheck();
	void SetFocusMenuIndex(int _Index);

	void StateUpdate(float _DeltaTime);

private:
	// Manager
	std::list<AActor*> AllCutSceneActors;

	//Character* SceneCharacter = nullptr;
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
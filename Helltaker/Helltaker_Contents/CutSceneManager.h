#pragma once

#include "ChapterManager.h"

#include "EngineBase/Transform.h"

class Chapter6;

// ���� :
class CutSceneManager : public ChapterManager
{
	friend Chapter6;

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
	void C_MenubarTextSet(int _Index, std::string_view _Text);
	void C_MenubarRenderActiveOff();
	void C_CharacterSetImage(std::string_view _Name);
	void C_CharacterSetTransform(FTransform _FTransform);

	int C_GetFocusMenuIndex() const
	{
		return FocusMenuIndex;
	}

	void C_StateChange(ECutSceneState _State);

	void C_AddFailOrder(int _Order)
	{
		FailOrder += _Order;
	}

	int C_GetFailOrder() const
	{
		return FailOrder;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart() override;
	
	virtual void SelectStart();
	virtual void SelectMenu() {};

	virtual void BadEndStart();
	virtual void BadEndSetting();
	virtual void FailOrderCheck();
	void FailOrderInputCheck();
	void ChapterRestart();

	virtual void SuccessStart();

private:
	void C_StateUpdate(float _DeltaTime);

	void Enter(float _DeltaTime);
	void EnterStart() {};

	void Select(float _DeltaTime);

	void BadEnd(float _DeltaTime);

	void Success(float _DeltaTime);
	void SuccessEnd();

	void SetFocusMenuIndex(int _Index);

private:
	std::list<AActor*> AllCutSceneActors;

	Character* SceneCharacter = nullptr;
	Scene* Dialogue = nullptr;
	UI* Booper = nullptr;
	std::vector<UI*> MenuBar;
	int MenuBarCount = 2;
	int FocusMenuIndex = -1;

	int FailOrder = -1;
	
	ECutSceneState State = ECutSceneState::None;

	static bool IsLoad;
};

using HellTakerManager = CutSceneManager;
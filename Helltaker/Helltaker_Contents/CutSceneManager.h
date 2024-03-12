#pragma once

#include "ChapterManager.h"

#include "EngineBase/Transform.h"

class Chapter6;

// 설명 :
class CutSceneManager : public ChapterManager
{
	// 수정 (friend 제거 가능?)
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
	void C_CreateSceneBG();

	void C_SpawnDialogue(std::string_view _Name);
	void C_SpawnCharacter(
		std::string_view _Name,
		std::string_view _ImgName,
		std::string_view _Text = " ",
		const FVector& _Pos = { 0.0f, 0.0f },
		const FVector& _Scale = { 0.255f, 0.611f });

	void C_SpawnBooper();
	void C_SpawnMenubar(FVector _Pos = { 0.5f, 0.86f }, int _MenuBarCount = 2);

	void C_BooperTextSet(std::string_view _Text);
	void C_BooperTextSet(std::string_view _Text, bool _SoundPlay);
	void C_BooperChangeAnimation(std::string_view _AnimationName);
	void C_BooperSetTransform(const FTransform& _Trans);
	void C_BooperSetTextPosition(int _LineCount);
	void C_BooperImageRendererOn();
	void C_BooperImageRendererOff();
	void C_MenubarTextSet(int _Index, std::string_view _Text);
	void C_MenubarRenderActiveOff();
	void C_MenubarRenderActiveOn();
	void C_ChangeCharactrer(std::string_view _Name, const FTransform& _Trans);
	void C_CharacterSetImage(std::string_view _Name);
	void C_CharacterSetTransform(const FTransform& _Trans);
	void C_CreateCharacterAnimation(
		std::string_view _AnimationName, 
		std::string_view _ImageName,
		int _Start,	int _End,
		float _Inter,
		bool _Loop = true);

	void C_CreateCharacterAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		std::vector<int> _Indexs,
		float _Inter,
		bool _Loop = true);

	void C_ChangeCharacterAnimation(std::string_view _AnimationName);

	void C_ChangeDialogue(std::string_view _ImageName, const FTransform& _FTransform);

	int C_GetFocusMenuIndex() const
	{
		return FocusMenuIndex;
	}

	void C_AddFailOrder(int _Order)
	{
		FailOrder += _Order;
	}

	int C_GetFailOrder() const
	{
		return FailOrder;
	}

	Character* C_GetSceneCharacter() const
	{
		return SceneCharacter;
	}

	Scene* C_GetDialogue() const
	{
		return Dialogue;
	}

	void AllCutSceneActorOn();
	void AllCutSceneActorOff();

	void C_StateChange(ECutSceneState _State);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart() override;
	
	virtual void Enter(float _DeltaTime);
	virtual void EnterStart() {};

	virtual void SelectStart();
	virtual void Select();
	virtual void SelectMenu() {};
	bool FocusMenuBarCheck();

	virtual void BadEndStart();
	virtual void BadEndSetting();
	virtual void FailOrderCheck();
	void FailOrderInputCheck();
	void ChapterRestart();

	void ResetCheck() override;

	virtual void SuccessStart();
	virtual void Success(float _DeltaTime);
	virtual void SuccessEnd();

private:
	void C_StateUpdate(float _DeltaTime);

	void BadEnd();

	void SetFocusMenuIndex(int _Index);

private:
	// Manager
	std::list<AActor*> AllCutSceneActors;
	
	Character* SceneCharacter = nullptr;
	Scene* Dialogue = nullptr;
	UI* Booper = nullptr;

	std::vector<UI*> MenuBar;
	int MenuBarCount = -1;
	int FocusMenuIndex = -1;
	static const FVector FocusMenuScale;
	static const FVector UnFocusMenuScale;

	int FailOrder = -1;
	
	ECutSceneState State = ECutSceneState::None;

	static bool IsLoad;
};

using HellTakerManager = CutSceneManager;
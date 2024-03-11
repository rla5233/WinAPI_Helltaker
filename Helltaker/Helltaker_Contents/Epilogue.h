#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Epilogue : public HellTakerManager
{
public:
	// constructor destructor
	Epilogue();
	~Epilogue();
	
	// delete Function
	Epilogue(const Epilogue& _Other) = delete;
	Epilogue(Epilogue&& _Other) noexcept = delete;
	Epilogue& operator=(const Epilogue& _Other) = delete;
	Epilogue& operator=(Epilogue&& _Other) noexcept = delete;

	void M_SpawnDemon(Point _Point, std::string_view _Name, const FTransform& _FTransform) override;

	void StateChange(EEpilogueState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;

	void CutSceneCheck() override;
	void CutSceneStart() override;

	void Enter(float _DeltaTime) override;
	void EnterStart() override;

private:
	void LucyCutSceneStart();
	void LucyCutScene( );
	void LucyCutScene1();
	void LucyCutScene2();
	void LucyCutScene3();
	void LucyCutScene4();
	void LucyCutScene5();
	void LucyCutScene6();
	void LucyCutScene7();

	void ModCutSceneStart();
	void ModCutScene();
	void ModCutScene1();
	void ModCutScene2();
	void ModCutScene3();
	void ModCutScene4();
	void ModCutScene5();
	void ModCutScene6();

	void JusCutSceneStart();
	void JusCutScene();
	void JusCutScene1();
	void JusCutScene2();
	void JusCutScene3();
	void JusCutScene4();
	void JusCutScene5();
	void JusCutScene6();
	void JusCutScene7();

	void SpawnPolice();
	void GoBackChapter();

	void StateUpdate(float _DeltaTime);

private:
	int OrderCount = -1;

	std::map<std::string, bool> CanCutScene;
	std::string DemonKeyName = "";
	
	EEpilogueState State = EEpilogueState::None;

	static const std::vector<const char*> Lucy_Script;
	static const std::vector<const char*> Mod_Script;
	static const std::vector<const char*> Jus_Script;
	static bool IsLoad;
};


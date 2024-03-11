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

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	void CutSceneCheck() override;
	void CutSceneStart() override;

	void Enter(float _DeltaTime) override;
	void EnterStart() override;

private:
	void SpawnPolice();

private:
	int OrderCount = -1;

	std::map<std::string, bool> CanCutScene;
	std::string DemonKeyName = "";
	
	EEpilogueState State = EEpilogueState::None;

	static const std::vector<const char*> Epilogue_Script;
	static bool IsLoad;
};


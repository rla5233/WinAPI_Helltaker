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

	void StateChange(EEpilogueState _State);

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	void Tick(float _DeltaTime) override;

	void CutSceneCheck() override;

private:
	void SpawnPolice();

	void StateUpdate(float _DeltaTime);

private:
	int OrderCount = -1;
	
	EEpilogueState State = EEpilogueState::None;

	static const std::vector<const char*> Epilogue_Script;
	static bool IsLoad;
};


#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class EpilogueOpening : public HellTakerManager
{
public:
	// constructor destructor
	EpilogueOpening();
	~EpilogueOpening();
	
	// delete Function
	EpilogueOpening(const EpilogueOpening& _Other) = delete;
	EpilogueOpening(EpilogueOpening&& _Other) noexcept = delete;
	EpilogueOpening& operator=(const EpilogueOpening& _Other) = delete;
	EpilogueOpening& operator=(EpilogueOpening&& _Other) noexcept = delete;

	void StateChange(EEpilogueState _State);

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	void Tick(float _DeltaTime) override;

	void ChangeChapter();

private:
	void EnterStart();
	void Enter();

	void Enter1();
	void EnterCutScene();

	void ChangeStart();
	void Change();

	void StateUpdate(float _DeltaTime);

private:
	int OrderCount = -1;

	EEpilogueState State = EEpilogueState::None;

	static const std::vector<const char*> Epil_Opening_Script;
	static bool IsLoad;
};


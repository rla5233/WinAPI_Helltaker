#pragma once

#include "SinCutSceneManager.h"

// Ό³Έν :
class SinChapter4 : public SinCutSceneManager
{
public:
	// constructor destructor
	SinChapter4();
	~SinChapter4();
	
	// delete Function
	SinChapter4(const SinChapter4& _Other) = delete;
	SinChapter4(SinChapter4&& _Other) noexcept = delete;
	SinChapter4& operator=(const SinChapter4& _Other) = delete;
	SinChapter4& operator=(SinChapter4&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void Phase1_Start() override;
	void Phase2_Start() override;

	void CutSceneStart() override;

	// CutScene
	void EnterStart() override;
	void Enter(float _DeltaTime) override;

	void SelectStart() override;
	void SelectMenu() override;

	void ChangeChapter() override;

private:
	int OrderCount = -1;

	static const std::vector<const char*> SinChap4_Script;
	static bool IsLoad;
};


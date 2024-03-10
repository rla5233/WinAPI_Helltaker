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
	void Enter(float _DeltaTime) override;

	void SelectStart() override;
	void SelectMenu() override;

	void ChangeChapter() override;

private:
	void Select1();
	void Select2();
	void Select3();
	void Select4();
	void Select5();
	void Select6();
	void Select7();
	void Select8();
	void Select9();
	void Select10();
	void Select11();
	void Select12();
	void Select13();

private:
	int OrderCount = -1;

	static const std::vector<const char*> SinChap4_Script;
	static bool IsLoad;
};


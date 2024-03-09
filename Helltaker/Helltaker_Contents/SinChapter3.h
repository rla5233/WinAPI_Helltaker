#pragma once

#include "SinCutSceneManager.h"

// Ό³Έν :
class SinChapter3 : public SinCutSceneManager
{
public:
	// constructor destructor
	SinChapter3();
	~SinChapter3();

	// delete Function
	SinChapter3(const SinChapter3& _Other) = delete;
	SinChapter3(SinChapter3&& _Other) noexcept = delete;
	SinChapter3& operator=(const SinChapter3& _Other) = delete;
	SinChapter3& operator=(SinChapter3&& _Other) noexcept = delete;

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
	void Enter1();
	void Enter2();
	void Enter3();
	void Enter4();
	void Enter5();
	void Enter6();
	void Enter7();

	void Select1();
	void Select2();
	void Select3();
	void Select4();

private:
	int OrderCount = -1;

	static const std::vector<const char*> SinChap3_Script;
	static bool IsLoad;
};

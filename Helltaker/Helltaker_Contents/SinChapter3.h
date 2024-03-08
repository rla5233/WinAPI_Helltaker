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

	void ChangeChapter() override;

private:


private:
	int OrderCount = -1;

	static const std::vector<const char*> SinChap3_Script;
	static bool IsLoad;
};

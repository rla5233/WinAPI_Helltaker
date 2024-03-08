#pragma once

#include "SinCutSceneManager.h"

// Ό³Έν :
class SinChapter2 : public SinManager
{
public:
	// constructor destructor
	SinChapter2();
	~SinChapter2();

	// delete Function
	SinChapter2(const SinChapter2& _Other) = delete;
	SinChapter2(SinChapter2&& _Other) noexcept = delete;
	SinChapter2& operator=(const SinChapter2& _Other) = delete;
	SinChapter2& operator=(SinChapter2&& _Other) noexcept = delete;

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

	static const std::vector<const char*> SinChap2_Script;
	static bool IsLoad;
};

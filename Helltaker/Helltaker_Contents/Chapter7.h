#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter7 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter7();
	~Chapter7();

	// delete Function
	Chapter7(const Chapter7& _Other) = delete;
	Chapter7(Chapter7&& _Other) noexcept = delete;
	Chapter7& operator=(const Chapter7& _Other) = delete;
	Chapter7& operator=(Chapter7&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void SelectStart() override;
	void SelectMenu() override;

	void SuccessStart() override;

private:

	static bool IsLoad;
};

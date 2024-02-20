#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter4 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter4();
	~Chapter4();

	// delete Function
	Chapter4(const Chapter4& _Other) = delete;
	Chapter4(Chapter4&& _Other) noexcept = delete;
	Chapter4& operator=(const Chapter4& _Other) = delete;
	Chapter4& operator=(Chapter4&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void SelectStart() override;
	void SelectMenu() override;

	void BadEndStart() override;
	void BadEndSetting() override;

	void SuccessStart() override;

private:

	static bool IsLoad;
};

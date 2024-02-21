#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter8 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter8();
	~Chapter8();

	// delete Function
	Chapter8(const Chapter8& _Other) = delete;
	Chapter8(Chapter8&& _Other) noexcept = delete;
	Chapter8& operator=(const Chapter8& _Other) = delete;
	Chapter8& operator=(Chapter8&& _Other) noexcept = delete;

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

#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter2 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter2();
	~Chapter2();
	
	// delete Function
	Chapter2(const Chapter2& _Other) = delete;
	Chapter2(Chapter2&& _Other) noexcept = delete;
	Chapter2& operator=(const Chapter2& _Other) = delete;
	Chapter2& operator=(Chapter2&& _Other) noexcept = delete;

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


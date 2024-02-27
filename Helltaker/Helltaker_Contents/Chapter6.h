#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter6 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter6();
	~Chapter6();
	
	// delete Function
	Chapter6(const Chapter6& _Other) = delete;
	Chapter6(Chapter6&& _Other) noexcept = delete;
	Chapter6& operator=(const Chapter6& _Other) = delete;
	Chapter6& operator=(Chapter6&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void SelectStart() override;
	void SelectMenu() override;

	void FailOrderCheck() override;
	void BadEndStart() override;

	void SuccessStart() override;

private:
	void BadEndSetting1();
	void BadEndSetting2();

private:

	static const std::vector<const char*> Chap6_Script;
	static bool IsLoad;
};


#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter5 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter5();
	~Chapter5();
	
	// delete Function
	Chapter5(const Chapter5& _Other) = delete;
	Chapter5(Chapter5&& _Other) noexcept = delete;
	Chapter5& operator=(const Chapter5& _Other) = delete;
	Chapter5& operator=(Chapter5&& _Other) noexcept = delete;

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

	static const std::vector<const char*> Chap5_Script;
	static bool IsLoad;
};


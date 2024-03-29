#pragma once

#include "CutSceneManager.h"

// ���� :
class Chapter1 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter1();
	~Chapter1();

	// delete Function
	Chapter1(const Chapter1& _Other) = delete;
	Chapter1(Chapter1&& _Other) noexcept = delete;
	Chapter1& operator=(const Chapter1& _Other) = delete;
	Chapter1& operator=(Chapter1&& _Other) noexcept = delete;

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
	
	static const std::vector<const char*> Chap1_Script;
	static bool IsLoad;
};

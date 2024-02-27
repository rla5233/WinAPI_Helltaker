#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter3 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter3();
	~Chapter3();
	
	// delete Function
	Chapter3(const Chapter3& _Other) = delete;
	Chapter3(Chapter3&& _Other) noexcept = delete;
	Chapter3& operator=(const Chapter3& _Other) = delete;
	Chapter3& operator=(Chapter3&& _Other) noexcept = delete;

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

	static const std::vector<const char*> Chap3_Script;
	static bool IsLoad;
};


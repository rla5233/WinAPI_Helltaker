#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class ChapterSin : public HellTakerManager
{
public:
	// constructor destructor
	ChapterSin();
	~ChapterSin();

	// delete Function
	ChapterSin(const ChapterSin& _Other) = delete;
	ChapterSin(ChapterSin&& _Other) noexcept = delete;
	ChapterSin& operator=(const ChapterSin& _Other) = delete;
	ChapterSin& operator=(ChapterSin&& _Other) noexcept = delete;

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

	static const std::vector<const char*> ChapSin_Script1;
	static const std::vector<const char*> ChapSin_Script2;
	static bool IsLoad;
};

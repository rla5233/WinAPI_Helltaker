#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class SinOpening : public HellTakerManager
{
public:
	// constructor destructor
	SinOpening();
	~SinOpening();

	// delete Function
	SinOpening(const SinOpening& _Other) = delete;
	SinOpening(SinOpening&& _Other) noexcept = delete;
	SinOpening& operator=(const SinOpening& _Other) = delete;
	SinOpening& operator=(SinOpening&& _Other) noexcept = delete;

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

	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};

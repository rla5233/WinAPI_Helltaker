#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter9 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter9();
	~Chapter9();

	// delete Function
	Chapter9(const Chapter9& _Other) = delete;
	Chapter9(Chapter9&& _Other) noexcept = delete;
	Chapter9& operator=(const Chapter9& _Other) = delete;
	Chapter9& operator=(Chapter9&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneCheck() override;
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void SelectStart() override;
	void SelectMenu() override;

	void BadEndStart() override;
	void BadEndSetting() override;

	void SuccessStart() override;

private:
	Point EndPoint = Point::Zero;

	static const std::vector<const char*> Chap9_Script;
	static bool IsLoad;
};

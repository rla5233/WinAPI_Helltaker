#pragma once

#include "ChapterManager.h"

// Ό³Έν :
class Chapter1 : public ChapterManager
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

	void ChooseMenuBar();
	void EnterChooseMenuCheck();

protected:
	void BeginPlay() override;

	void LevelStart(ULevel* _PrevLevel) override;

	void CutScene(float _DeltaTime) override; 
	void CutSceneStart() override;

private:
	


	static bool IsLoad;
};

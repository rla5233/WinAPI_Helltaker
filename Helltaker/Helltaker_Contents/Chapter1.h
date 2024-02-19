#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
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

	void CutSceneStart() override;
	void SelectStart() override;
	void SelectMenu() override;
private:
	
	static bool IsLoad;
};

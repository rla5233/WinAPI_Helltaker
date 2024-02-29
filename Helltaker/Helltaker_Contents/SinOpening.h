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
	void Enter(float _DeltaTime) override;

private:
	void EnterOrder1();
	void EnterOrder2();

	void SpawnDialBG_Hell();
	void SpawnDialBG_Sin();

private:
	int EnterOrder = -1;

	Scene* DialBG_Hell = nullptr;
	Scene* DialBG_Sin = nullptr;

	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};

#pragma once

#include "CutSceneManager.h"

// ���� :
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
	void EnterStart() override;
	void Enter(float _DeltaTime) override;

private:
	void EnterOrder1();

private:
	int EnterOrder = -1;

	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};

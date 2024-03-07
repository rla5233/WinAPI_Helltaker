#pragma once

#include "SinCutSceneManager.h"

// Ό³Έν :
class SinOpening : public SinManager
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
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	void CutScene(float _DeltaTime) override;

	// CutScene
	void EnterStart() override;
	void Enter(float _DeltaTime) override;

private:
	void Enter1(float _DeltaTime);

	void TransitionCheck();

private:
	int EnterOrder = -1;

	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};

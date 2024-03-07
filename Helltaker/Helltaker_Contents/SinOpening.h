#pragma once

#include "SinCutSceneManager.h"

// ���� :
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
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	
private:


	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};

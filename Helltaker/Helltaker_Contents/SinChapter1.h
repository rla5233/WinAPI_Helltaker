#pragma once

#include "SinCutSceneManager.h"

// Ό³Έν :
class SinChapter1 : public SinManager
{
public:
	// constructor destructor
	SinChapter1();
	~SinChapter1();
	
	// delete Function
	SinChapter1(const SinChapter1& _Other) = delete;
	SinChapter1(SinChapter1&& _Other) noexcept = delete;
	SinChapter1& operator=(const SinChapter1& _Other) = delete;
	SinChapter1& operator=(SinChapter1&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void Phase1_Start() override;
	void Phase2_Start() override;

	void CutSceneStart() override;

	// CutScene
	void EnterStart() override;
	void Enter(float _DeltaTime) override;

	void EndStart() override;

	void ChangeChapter() override;

private:
	void Enter1();
	void Enter2();
	void Enter3();
	void Enter4();

private:
	int OrderCount = -1;

	static const std::vector<const char*> SinChap1_Script;
	static bool IsLoad;
};


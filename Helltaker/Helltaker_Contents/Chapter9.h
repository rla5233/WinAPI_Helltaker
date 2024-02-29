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

	void EndStart() override;
	void End(float _DeltaTime) override;

	// CutScene
	void Enter(float _DeltaTime) override;
	void EnterStart() override;

	void BadEndStart() override;
	void BadEndSetting() override;
	void FailOrderCheck() override;

private:
	void EndChapter9();

private:
	Point EndPoint = Point::Zero;
	int EnterOrder = -1;
	int EndOrder = -1;

	static const std::vector<const char*> Chap9_Script;
	static bool IsLoad;
};

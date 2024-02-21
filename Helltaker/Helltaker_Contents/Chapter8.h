#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Chapter8 : public HellTakerManager
{
public:
	// constructor destructor
	Chapter8();
	~Chapter8();

	// delete Function
	Chapter8(const Chapter8& _Other) = delete;
	Chapter8(Chapter8&& _Other) noexcept = delete;
	Chapter8& operator=(const Chapter8& _Other) = delete;
	Chapter8& operator=(Chapter8&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	// Chapter
	void CutSceneCheck() override;
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void Enter(float _DeltaTime) override;
	void EnterStart() override;

	void SelectStart() override;
	void SelectMenu() override;

	void BadEndStart() override;
	void BadEndSetting() override;

	void SuccessStart() override;

private:
	void EnterOrder0();
	void EnterOrder1();
	void EnterOrder2();

	void CreateDefaultBG();
	void SpawnSkeletonMan();

private:
	BackGround* M_DefaultBackGround = nullptr;
	Point EndPoint = Point::Zero;

	std::vector<Scene*> SkeletonMan;

	int EnterOrder = -1;

	static bool IsLoad;
};

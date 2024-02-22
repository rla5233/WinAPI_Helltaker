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
	void Success(float _DeltaTime) override;

private:
	void EnterOrder0(float _DeltaTime);
	void EnterOrder1(float _DeltaTime);
	void EnterOrder2(float _DeltaTime);
	void EnterOrder3(float _DeltaTime);
	void EnterOrder4();
	void EnterOrder5();

	void SuccessStart1();

	void CreateDefaultBG();
	void SpawnSkeletonMan();

private:
	BackGround* M_DefaultBackGround = nullptr;
	Point EndPoint = Point::Zero;

	std::vector<Scene*> SkeletonMan;
	int EnterOrder = -1;
	int SelectOrder = -1;
	
	const static float SkeletonCreateDelay;
	const static float SkeletonRenderDelay;
	const static float LuSwirl2RenderDelay;
	const static float LuIdleRenderDelay;
	float TimeCount = 0;

	static bool IsLoad;
};

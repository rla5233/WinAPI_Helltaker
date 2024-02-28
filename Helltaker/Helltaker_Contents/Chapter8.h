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
	void SuccessEnd() override;

private:
	void EnterOrder0(float _DeltaTime);
	void EnterOrder1(float _DeltaTime);
	void EnterOrder2(float _DeltaTime);
	void EnterOrder3(float _DeltaTime);
	void EnterOrder4(float _DeltaTime);
	void EnterOrder5();
	void EnterOrder6();

	void SuccessStart1();
	void SuccessStart2();
	void SuccessEnter();
	void SuccessEndScene();

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
	const static float LuSwirl1RenderDelay;
	const static float LuSwirl2RenderDelay;
	const static float LuIdleRenderDelay;
	float TimeCount = 0;

	static const std::vector<const char*> Chap8_Script;
	static bool IsLoad;
};

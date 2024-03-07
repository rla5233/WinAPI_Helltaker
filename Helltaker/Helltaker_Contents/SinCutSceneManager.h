#pragma once

#include "SinChapterManager.h"

// Ό³Έν :
class SinCutSceneManager : public SinChapterManager
{
public:
	// constructor destructor
	SinCutSceneManager();
	~SinCutSceneManager();
	
	// delete Function
	SinCutSceneManager(const SinCutSceneManager& _Other) = delete;
	SinCutSceneManager(SinCutSceneManager&& _Other) noexcept = delete;
	SinCutSceneManager& operator=(const SinCutSceneManager& _Other) = delete;
	SinCutSceneManager& operator=(SinCutSceneManager&& _Other) noexcept = delete;

	void C_CreateSceneBG();

	void CutSceneStart();

	void C_StateChange(ESinSceneState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void EnterStart();
	void Enter(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::list<AActor*> AllCutSceneActors;



	ESinSceneState State = ESinSceneState::None;
	static bool IsLoad;
};

using SinManager = SinCutSceneManager;
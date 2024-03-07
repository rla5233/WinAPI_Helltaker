#pragma once

#include <EngineCore/Level.h>

class BackGround;
class Scene;

// ���� :
class Opening : public ULevel
{
public:
	// constructor destructor
	Opening();
	~Opening();

	// delete Function
	Opening(const Opening& _Other) = delete;
	Opening(Opening&& _Other) noexcept = delete;
	Opening& operator=(const Opening& _Other) = delete;
	Opening& operator=(Opening&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void LogoFadeIn(float _DeltaTime);
	void DelayTime(float _DeltaTime);
	void LogoFadeOut(float _DeltaTime);
	void EnterMainMenu();

private:
	BackGround* OpeningBG = nullptr;
	Scene* UnityLogo = nullptr;
	
	int OpeningOrder = -1;
	float DelayTimeCount = 0.0f;
	static const float FadeOutDelayTime;
};

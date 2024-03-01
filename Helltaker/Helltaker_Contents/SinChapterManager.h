#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;

// Ό³Έν :
class SinChapterManager : public ULevel
{
public:
	// constructor destructor
	SinChapterManager();
	~SinChapterManager();
	
	// delete Function
	SinChapterManager(const SinChapterManager& _Other) = delete;
	SinChapterManager(SinChapterManager&& _Other) noexcept = delete;
	SinChapterManager& operator=(const SinChapterManager& _Other) = delete;
	SinChapterManager& operator=(SinChapterManager&& _Other) noexcept = delete;

	void M_CreateSinMap();
	void M_CreateSinBG(std::string_view _Name);
	void M_CreateSinPit();
	void M_CreateSinGear();

	void M_CreateSinPanel();
	void M_CreateSinPyre();

	void M_CreateSinShield();
	void M_CreateSinSkull();
	void M_CreateSinChain();
	void M_CreateSinPiston();

	void M_CreateSinBridge();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	void M_StateChange(ESinState _State);

private:
	void Phase1Start();
	void Phase1(float _DeltaTime);

	void AllSinPitMoveOn();
	void AllSinPitMoveUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::list<AActor*> AllMapRenderActors;

	std::list<SinComponent*> AllSinPit;
	static const float SinPitSpeedY;
	static const float SinPitInterValY;

	SinComponent* SinGear = nullptr;

	std::vector<SinComponent*> SinPyre;
	static const float SinFireInter;

	std::vector<SinComponent*> SinBridge;
	
	SinComponent* UpPiston = nullptr;
	SinComponent* DownPiston = nullptr;
	SinComponent* Skull = nullptr;
	std::list<SinComponent*> AllSinChain;

	ESinState State = ESinState::None;
	static bool IsLoad;
};


#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;
class Sin_Thorn;
class HeroLife;
class Bridge;
class Gear;
class Pit;

// ���� :
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

	void M_CreateSinShield();


	void M_CreateThorn();
	void M_CreateSinHeroLife();

	//
	void M_CreateSinSkull();
	void M_CreateSinChain();
	void M_CreateSinPiston();

	void M_CreateSinBridge();

	size_t GetSinPitSize() const
	{
		return SinPit.size();
	}

	size_t GetSinBridgeSize() const
	{
		return SinBridge.size();
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	void M_StateChange(ESinState _State);

private:
	void Phase1Start();
	void Phase1(float _DeltaTime);

	void IntroStart();
	void Intro(float _DeltaTime);

	void SinPitMoveOn();
	void SinBridgeMoveOn();
	void SinChainMoveOn();
	void SinChainMoveUpdate(float _DeltaTime);

	void AllThornMoveOn();

	void StateUpdate(float _DeltaTime);

private:
	std::list<AActor*> AllMapRenderActors;

	std::vector<Pit*> SinPit;
	Gear* SinGear = nullptr;

	std::vector<Bridge*> SinBridge;

	HeroLife* SinHeroLife = nullptr;

	//
	SinComponent* UpPiston = nullptr;
	SinComponent* DownPiston = nullptr;
	SinComponent* Skull = nullptr;

	std::vector<SinComponent*> SinChain;
	static const FVector SinChainSCale;
	static const float SinChainSpeedY;

	std::vector<std::vector<Sin_Thorn*>> UpThorn;
	std::vector<std::vector<Sin_Thorn*>> DownThorn;


	ESinState State = ESinState::None;
	static bool IsLoad;
};


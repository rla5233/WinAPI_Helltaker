#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;
class Sin_Thorn;
class Sin_Hero;
class HeroLife;
class Bridge;
class Piston;
class Chain;
class Skull;
class Gear;
class Pit;

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

	void M_CreateSinShield();

	void M_CreateSinPiston();
	void M_CreateSinSkull();
	void M_CreateSinChain();

	void M_CreateSinBridge();

	void M_CreateThorn();
	void M_CreateSinHeroLife();

	void M_SpawnHero();

	size_t GetSinPitSize() const
	{
		return SinPit.size();
	}

	size_t GetSinBridgeSize() const
	{
		return SinBridge.size();
	}

	size_t GetSinChainSize() const
	{
		return SinChain.size();
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
	void AllThornMoveOn();

	void HeroDelayTimeUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::list<AActor*> AllMapRenderActors;

	std::vector<Pit*> SinPit;
	Gear* SinGear = nullptr;

	Piston* UpPiston = nullptr;
	Piston* DownPiston = nullptr;
	Skull* SinSkull = nullptr;
	std::vector<Chain*> SinChain;

	std::vector<Bridge*> SinBridge;

	std::vector<std::vector<Sin_Thorn*>> UpThorn;
	std::vector<std::vector<Sin_Thorn*>> DownThorn;

	HeroLife* SinHeroLife = nullptr;
	Sin_Hero* PlayerHero = nullptr;
	static const float HeroDelayTime;
	float HeroDelayTimeCount = HeroDelayTime;

	ESinState State = ESinState::None;
	static bool IsLoad;
};


#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;
class SmallChain;
class ChainLink;
class Sin_Thorn;
class Sin_Hero;
class HitChain;
class HeroLife;
class Bridge;
class Piston;
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
	void M_CreateSinChainLink();

	void M_CreateSinBridge();

	void M_CreateThorn();
	void M_CreateSinHeroLife();

	void M_SpawnHero();

	void M_CreateSmallChain(ESinSmallChainType _Type, int _PhaseNum, int _PosIndex, int _VecIndex);
	void M_SetSmallChainVecSize(int _Size, int _PhaseNum);

	void M_CreateHitChain(ESinHitChainType _Type, int _PointY);

	float M_GetSpeedY() const
	{
		return SpeedY;
	}

	float M_GetMoveYSum() const
	{
		return MoveYSum;
	}

	size_t GetSinPitSize() const
	{
		return SinPit.size();
	}

	size_t GetSinBridgeSize() const
	{
		return SinBridge.size();
	}

	size_t GetSinChainLinkSize() const
	{
		return SinChain.size();
	}

	Skull* GetSkull() const
	{
		return SinSkull;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void Phase1Start();
	virtual void Phase2Start();

	void M_StateChange(ESinState _State);

private:
	void IntroStart();
	void Intro(float _DeltaTime);

	void Phase1(float _DeltaTime);
	void Phase1SmallChainUpdate(float _DeltaTime);
	void SpeedY_Update(float _DeltaTime);

	void SinPitMoveOn();
	void SinBridgeMoveOn();
	void SinChainMoveOn();
	void AllThornMoveOn();

	void Phase2(float _DeltaTime);

	void HeroDelayTimeUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

	void DebugMode();

private:
	std::list<AActor*> AllMapRenderActors;
	std::map<__int64, HitChain*> AllHitChain;

	std::vector<Pit*> SinPit;
	Gear* SinGear = nullptr;

	Piston* UpPiston = nullptr;
	Piston* DownPiston = nullptr;
	Skull* SinSkull = nullptr;
	std::vector<ChainLink*> SinChain;

	std::vector<Bridge*> SinBridge;

	std::vector<std::vector<Sin_Thorn*>> UpThorn;
	std::vector<std::vector<Sin_Thorn*>> DownThorn;

	HeroLife* SinHeroLife = nullptr;
	Sin_Hero* PlayerHero = nullptr;
	static const float HeroDelayTime;
	float HeroDelayTimeCount = HeroDelayTime;

	static const FVector SmallChainStartPos;
	std::vector<std::list<SmallChain*>> Phase1_SmallChain;
	int Phase1_SmallChainVecSize = -1;
	
	std::vector<std::list<SmallChain*>> Phase2_SmallChain;
	int Phase2_SmallChainVecSize = -1;

	static const float Phase1_DelayTime;
	float PhaseDelayTimeCount = 0.0f;
	int PhaseSmallChainVec_Index = -1;

	static const float MaxSpeedY;
	float SpeedY = 50.0f;
	
	float MoveYSum = 0;

	ESinState State = ESinState::None;
	static bool IsLoad;
};


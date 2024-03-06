#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;
class SmallChain;
class HitChainHp;
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
class UI;

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
	void M_CreateHitChainHp(std::string_view _Name = " ");

	bool HitChainHitCheck(SinTile _Point);
	void HitChainDeathUpdate(SinTile _Point);

	static float GetStartPosY()
	{
		return StartPosY;
	}

	float M_GetSpeedY() const
	{
		return SpeedY;
	}

	float M_GetMoveYSum() const
	{
		return MoveYSum;
	}

	void AddBridgeResetCount(int _Count)
	{
		BridgeResetCount += _Count;
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

	HeroLife* GetSinHeroLife() const
	{
		return SinHeroLife;
	}

	Sin_Hero* GetPlayerHero() const
	{
		return PlayerHero;
	}

	HitChainHp* GetHitChainHp() const
	{
		return SinHitChainHp;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void Phase1_Start();
	virtual void Phase2_Start();

	void M_StateChange(ESinState _State);

private:
	void IntroStart();
	void Intro(float _DeltaTime);

	void Phase1(float _DeltaTime);
	void Phase1_SmallChainUpdate(float _DeltaTime);
	void Phase1_SpeedY_Update1(float _DeltaTime);
	void Phase1_SpeedY_Update2(float _DeltaTime);
	void BridgeResetCheck();

	void SinPitMoveOn();
	void SinBridgeMoveOn();
	void SinChainMoveOn();
	void AllThornMoveOn();

	void Phase2(float _DeltaTime);

	void HeroDelayTimeUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

	void DebugMode();

private:
	std::list<AActor*> AllMapRenderActors; //
	std::map<__int64, HitChain*> AllHitChain; //
	HitChainHp* SinHitChainHp = nullptr;

	std::vector<Pit*> SinPit;
	Gear* SinGear = nullptr;

	Piston* UpPiston = nullptr;
	Piston* DownPiston = nullptr;
	Skull* SinSkull = nullptr;
	std::vector<ChainLink*> SinChain;

	std::vector<Bridge*> SinBridge;
	int BridgeResetCount = 0;

	std::vector<std::vector<Sin_Thorn*>> UpThorn;
	std::vector<std::vector<Sin_Thorn*>> DownThorn;

	HeroLife* SinHeroLife = nullptr;
	Sin_Hero* PlayerHero = nullptr;
	static const float HeroDelayTime;
	float HeroDelayTimeCount = HeroDelayTime;

	static const FVector SmallChainStartPos;
	std::vector<std::list<SmallChain*>> Phase1_SmallChain; //
	static const float Phase1_DelayTime;
	int Phase1_SmallChainVecSize = -1;
	int Phase1_Order = -1;
	float AccY = 0.0f;
	
	std::vector<std::list<SmallChain*>> Phase2_SmallChain; //
	int Phase2_SmallChainVecSize = -1;

	float PhaseDelayTimeCount = 0.0f;
	int PhaseSmallChainVec_Index = -1;

	static const float MaxSpeedY;
	float SpeedY = 50.0f;
	float MoveYSum = 0;

	static const float StartPosY;

	ESinState State = ESinState::None;
	static bool IsLoad;
};


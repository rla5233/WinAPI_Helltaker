#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>
#include <set>

class SinComponent;
class SmallChain;
class HitChainHp;
class ChainLink;
class Sin_Thorn;
class Sin_Demon;
class Sin_Hero;
class HitChain;
class HeroLife;
class Bridge;
class Piston;
class Skull;
class Scene;
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

	void CreateTransition();
	void TransitionOn();
	
	void M_CreateSinMap(int _ChapterNum);

	void M_CreateSinBG(std::string_view _Name);
	void M_CreateSinPit();
	void M_CreateSinGear();

	void M_CreateSinShield();

	void M_CreateSinPiston();
	void M_CreateSinSkull();
	void M_CreateSinChainLink();

	void M_CreateSinBridge();

	void M_CreateThorn();
	void M_CreateSinHeroLife(int _ChapterNum);

	void M_SpawnHero();
	void M_SpawnDemon();

	void M_CreateSmallChain(
		ESinSmallChainType _Type,
		ESinPhase _Phase,
		int _PosIndex, 
		int _VecIndex);

	void M_CreateSmallVerChain_P1(int _PosIndex, int _VecIndex);
	void M_CreateSmallHorChain_P1(int _PosIndex, int _VecIndex);

	void M_SetSmallChainVecSize(int _Size, ESinPhase _Phase);

	void M_SmallChainDeathCall(int _VecIndex);

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
		return SinChainLink.size();
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

	Scene* GetTransitionActor() const
	{
		return TransitionActor;
	}

	template<typename Chapter>
	void CreateChapter(std::string_view _Name)
	{
		if (false == ChapterSet.contains(_Name.data()))
		{
			GEngine->CreateLevel<Chapter>(_Name);
		}
	}

	void AddChapterSet(std::string _Name)
	{
		if (true == ChapterSet.contains(_Name))
		{
			MsgBoxAssert("Chapter Already Exist");
		}

		ChapterSet.insert(_Name);
	}

	void M_StateChange(ESinState _State);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void Phase1_Start();
	virtual void Phase2_Start();

	virtual void CutSceneStart();
	virtual void CutScene(float _DeltaTime);

	virtual void ResetCheck();

	virtual void ChangeChapter() {};

private:
	void IntroStart();
	void Intro(float _DeltaTime);
	void TransitionCheck(float _DeltaTime);
	void Phase1_Check();

	void Phase1(float _DeltaTime);
	void Phase1_SmallChainUpdate(float _DeltaTime);
	void Phase1_SpeedY_Update1(float _DeltaTime);
	void Phase1_SpeedY_Update2(float _DeltaTime);
	void BridgeResetCheck();

	void SinPitMoveOn();
	void SinBridgeMoveOn();
	void SinChainLinkMoveOn();
	void AllThornMoveOn();

	void SinPitMoveOff();
	void SinBridgeMoveOff();
	void SinChainLinkMoveOff();
	void AllThornMoveOff();

	void Phase2(float _DeltaTime);
	void HitChainCheck();
	void JudgeAppear(float _DeltaTime);

	void ResetStart();
	void Reset(float _DeltaTime);

	void HeroDelayTimeUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

	void DebugMode();

private:
	// Manager
	std::list<AActor*> AllMapRenderActors;
	std::map<__int64, HitChain*> AllHitChain;
	std::vector<std::list<SmallChain*>> Phase1_SmallChain;
	std::vector<std::list<SmallChain*>> Phase2_SmallChain;

	HitChainHp* SinHitChainHp = nullptr;

	Gear* SinGear = nullptr;

	Piston* UpPiston = nullptr;
	Piston* DownPiston = nullptr;
	Skull* SinSkull = nullptr;

	std::vector<Pit*> SinPit;
	std::vector<ChainLink*> SinChainLink;
	std::vector<Bridge*> SinBridge;
	int BridgeResetCount = 0;

	std::vector<Sin_Thorn*> UpThorn;
	std::vector<Sin_Thorn*> DownThorn;

	HeroLife* SinHeroLife = nullptr;
	Sin_Hero* PlayerHero = nullptr;
	static const float HeroDelayTime;
	float HeroDelayTimeCount = HeroDelayTime;

	static const float IntroDelayTime;
	int Intro_Order = -1;

	static const FVector SmallChainStartPos;
	static float SmallChainDelayTime;
	int Phase1_SmallChainVecSize = -1;
	int Phase1_Order = -1;
	float AccY = 0.0f;
	
	int Phase2_SmallChainVecSize = -1;
	int Phase2_Order = -1;

	float PhaseTimeCount = 0.0f;
	int SmallChainVec_Index = -1;

	static const float Phase1_StartDelayTime;
	static const float CutSceneDelayTime;
	float TimeCount = 0.0f;

	static const float MaxSpeedY;
	float SpeedY = 50.0f;
	float MoveYSum = 0;

	static const float StartPosY;

	Sin_Demon* Judge = nullptr;

	Scene* TransitionActor = nullptr;
	static const float TransitionInter;

	ESinState State = ESinState::None;
	static bool IsLoad;
	static std::set<std::string> ChapterSet;
};


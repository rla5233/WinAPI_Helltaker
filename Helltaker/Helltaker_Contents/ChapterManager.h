#pragma once

#include "ContentsHelper.h"

#include <vector>
#include <set>

#include <EngineCore/Level.h>

class UEngineSoundPlayer;
class KeyComponent;
class BackGround;
class FTransform;
class Character;
class HitActor;
class Scene;
class Thorn;
class Demon;
class Hero;
class Text;
class UI;

class Epilogue;

class TileInfo
{
public:
	bool IsVaild = false;
	bool IsThorn = false;
	HitActor* Other = nullptr;
};

// ���� :
class ChapterManager : public ULevel
{
	friend Epilogue;

public:
	// constructor destructor
	ChapterManager();
	~ChapterManager();

	// delete Function
	ChapterManager(const ChapterManager& _Other) = delete;
	ChapterManager(ChapterManager&& _Other) noexcept = delete;
	ChapterManager& operator=(const ChapterManager& _Other) = delete;
	ChapterManager& operator=(ChapterManager&& _Other) noexcept = delete;

	void CreateBG(std::string_view _Name);
	void CreateTransition();
	void TransitionOn();
	Scene* GetTransitionActor() const
	{
		return TransitionActor;
	}

	FVector ChapterPointToLocation(Point _Point) const;
	
	const std::vector<std::vector<TileInfo>>& GetTileInfoVec() const
	{
		return TileInfoVec;
	}	

	// Map
	void M_CreateTileInfoVec(const std::vector<std::vector<bool>>& _Map);
	void M_SetChapterHitAcotrInfo(Point _Point, HitActor* const _HitActor);
	void M_SetChapterThornInfo(Point _Point, bool _IsUp);

	void M_CreateChapterUI(int _ChapterNumber);
	void M_SpawnHero(Point _Point, int _ActionPoint);
	void M_SpawnEpilHero(Point _Point);
	virtual void M_SpawnDemon(Point _Point, std::string_view _Name, const FTransform& _FTransform);
	void M_SpawnSkeleton(Point _Point);
	void M_SpawnStone(Point _Point, std::string_view _Name);
	void M_SpawnThorn(Point _Point, EThornState _State);
	void M_SpawnKeyComponent(Point _Point, EKeyComponentType _Type);
	void M_SetIsThornChange(bool _Value)
	{
		IsThornChange = _Value;
	}

	HitActor* M_GetHitActor(Point _Point) const;
	void M_DestroyHitActor(__int64 _Key);
	void M_ChangeThornState();
	void M_UpdateHeroActionPoint();
	void M_BottomTextRendererOff();
	FVector M_GetHeroLocation() const;
	Point M_GetHeroLocationPoint() const;
	Point M_GetHeroNextLocationPoint() const;
	EHeroState M_GetHeroState() const;

	void M_SetChapterStartLocation(FVector _Value);
	FVector M_GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	void M_SetCameraPosUpdate(bool _Value)
	{
		IsCameraPosUpdateOn = _Value;
	}

	void M_AddActorMap(AActor* const _Actor)
	{
		AllMapActors[reinterpret_cast<__int64>(_Actor)] = _Actor;
	}
	
	static UEngineSoundPlayer GetChapterBGM();

	void M_StateChange(EChapterState _State);

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

	bool IsKeyPoint();
	bool IsLockBoxPoint();
	void DeleteKey();
	void DeleteLockBox();

	void ReturnToChap(std::string_view _DemonName);

	void CameraPosUpdate(const FVector& _Pos);
	virtual void CutSceneCheck();
	
	void ChapterMainBGM_On();
	void ChapterMainBGM_Off();
	void ChapterMainBGM_SetVolume(float _Volume);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;
	
	void Idle(float _DeltaTime);

	virtual void CutSceneStart();
	virtual void ChangeChapter() {};
	
	virtual void EndStart();
	virtual void End(float _DeltaTime);

	virtual void ResetCheck();

	void M_InitChapterEndOrder()
	{
		ChapterEndOrder = 0;
	}

	void HeroDelayTimeUpdate(float _DeltaTime);

private:
	void IdleStart();

	void HeroDeathStart();
	void HeroDeath(float _DeltaTime);

	void CutScene(float _DeltaTime);

	void ResetStart();
	void Reset(float _DeltaTime);

	// Debug
	void DebugMode();
	void CreateDebugPoint();
	void DebugPointOn();
	void DebugPointOff();

	void M_StateUpdate(float _DeltaTime);

private:
	// Manager
	std::map<__int64, AActor*> AllMapActors;

	std::vector<std::vector<TileInfo>> TileInfoVec;
	std::list<Thorn*> AllThorn;
	std::list<Demon*> AllChapterDemon;

	FVector ChapterStartLocation = FVector::Zero;
	int ChapterEndOrder = -1;

	int ChapterNumber = -1;
	int ChapterWidth = -1;
	int ChapterHeight = -1;
	bool IsThornChange = false;
	bool IsCameraPosUpdateOn = false;

	static const float TransitionInter;
	Scene* TransitionActor = nullptr;
	BackGround* ChapterBG = nullptr;
	
	static const float HeroDelayTime;
	float HeroDelayTimeCount = HeroDelayTime;
	Hero* PlayerHero = nullptr;
	Text* HeroActionPoint = nullptr;
	Text* BottomText = nullptr;

	KeyComponent* LockBox = nullptr;
	KeyComponent* Key = nullptr;

	static UEngineSoundPlayer ChapterBGMPlayer;

	EChapterState State = EChapterState::None;

	static bool IsLoad;
	static std::set<std::string> ChapterSet;

	std::vector<std::vector<UI*>> DebugPoint;
};
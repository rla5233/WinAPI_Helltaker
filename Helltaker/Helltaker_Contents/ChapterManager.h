#pragma once

#include "ContentsHelper.h"

#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>

class HitActor;
class Scene;
class Thorn;
class Hero;

class TileInfo
{
public:
	bool IsVaild = false;
	bool IsThorn = false;
	HitActor* Other = nullptr;
};

// 설명 :
class ChapterManager : public ULevel
{
public:
	// constructor destructor
	ChapterManager();
	~ChapterManager();

	// delete Function
	ChapterManager(const ChapterManager& _Other) = delete;
	ChapterManager(ChapterManager&& _Other) noexcept = delete;
	ChapterManager& operator=(const ChapterManager& _Other) = delete;
	ChapterManager& operator=(ChapterManager&& _Other) noexcept = delete;

	FVector ChapterPointToLocation(FVector _Point) const;
	FVector ChapterPointToLocation(int _X, int _Y) const;
	
	void SetChapterStartLocation(int _X, int _Y);
	FVector GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	void SetChapterEndPoint(int _X, int _Y);

	const std::vector<std::vector<TileInfo>>& GetChapterInfoVec() const
	{
		return ChapterInfoVec;
	}

	void CreateChapterInfoVec(const std::vector<std::vector<bool>>& _Map);
	void SetChapterHitAcotrInfo(int _X, int _Y, HitActor* const _HitActor);
	void SetChapterThornInfo(int _X, int _Y, bool _IsUp);

	void CreateBG(std::string_view _Name);
	void CreateChapterUI();
	void CreateTransition();
	void SpawnHero(int _X, int _Y);
	void SpawnDemon(int _X, int _Y, std::string_view _Name);
	void SpawnSkeleton(int _X, int _Y);
	void SpawnStone(int _X, int _Y, std::string_view _Name);
	void SpawnThorn(int _X, int _Y, EThornState _State);

	HitActor* GetHitActor(FVector _Point);
	HitActor* GetHitActor(int _X, int _Y);
	void DestroyHitActor(__int64 _HitActor);
	void ChangeThornState();

	// 디버그 용
	void ShowLocationPoint();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	void Idle(float _DeltaTime);
	void IdleStart();

	void Transition(float _DeltaTime);
	void TransitionStart();

	void CutSecene(float _DeltaTime);
	void CutSeceneStart();

	void Reset(float _DeltaTime);
	void ResetStart();

	void StateUpdate(float _DeltaTime);
	void StateChange(EChapterState _State);

private:
	std::vector<std::vector<TileInfo>> ChapterInfoVec;
	std::map<__int64, AActor*> AllActors;
	std::vector<Thorn*> AllThorn;

	EChapterState State = EChapterState::None;
	FVector ChapterStartLocation = FVector::Zero;
	int EndPoint_X = -1;
	int EndPoint_Y = -1;

	int ChapterWidth = -1;
	int ChapterHeight = -1;

	Hero* PlayerHero = nullptr;
	Scene* TransitionActor = nullptr;
	const float TransitionInter = 0.0435f;

	static bool IsLoad;
};

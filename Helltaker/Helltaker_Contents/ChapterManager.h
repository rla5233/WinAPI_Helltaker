#pragma once

#include "ContentsHelper.h"

#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>

class BackGround;
class Character;
class HitActor;
class Scene;
class Thorn;
class Demon;
class Hero;
class Text;
class UI;

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

	FVector ChapterPointToLocation(FVector _Point) const;
	FVector ChapterPointToLocation(int _X, int _Y) const;
	
	const std::vector<std::vector<TileInfo>>& GetTileInfoVec() const
	{
		return TileInfoVec;
	}	

	// Map
	void M_CreateTileInfoVec(const std::vector<std::vector<bool>>& _Map);
	void M_SetChapterHitAcotrInfo(int _X, int _Y, HitActor* const _HitActor);
	void M_SetChapterThornInfo(int _X, int _Y, bool _IsUp);

	void M_CreateChapterUI(int _ChapterNumber);
	void M_SpawnHero(int _X, int _Y, int _ActionPoint);
	void M_SpawnDemon(int _X, int _Y, std::string_view _Name);
	void M_SpawnSkeleton(int _X, int _Y);
	void M_SpawnStone(int _X, int _Y, std::string_view _Name);
	void M_SpawnThorn(int _X, int _Y, EThornState _State);

	HitActor* M_GetHitActor(FVector _Point);
	HitActor* M_GetHitActor(int _X, int _Y);
	void M_DestroyHitActor(__int64 _HitActor);
	void M_ChangeThornState();
	void M_UpdateHeroActionPoint();

	void M_SetChapterStartLocation(int _X, int _Y);
	FVector M_GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	void M_SetChapterEndPoint(int _X, int _Y);

	void M_StateChange(EChapterState _State);
	
	// Debug
	void ShowLocationPoint();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart();
private:
	void Idle(float _DeltaTime);
	void IdleStart();

	void HeroDeath(float _DeltaTime);
	void HeroDeathStart();

	void CutScene(float _DeltaTime);

	void Reset(float _DeltaTime);
	void ResetStart();
	void ResetCheck();

	void End(float _DeltaTime);
	void EndStart();

	void M_StateUpdate(float _DeltaTime);

private:
	std::vector<std::vector<TileInfo>> TileInfoVec;
	std::map<__int64, AActor*> AllMapActors;
	std::list <Thorn*> AllThorn;


	EChapterState State = EChapterState::None;
	FVector ChapterStartLocation = FVector::Zero;
	int EndPoint_X = -1;
	int EndPoint_Y = -1;

	int ChapterNumber = -1;
	int ChapterWidth = -1;
	int ChapterHeight = -1;

	const float TransitionInter = 0.0435f;
	BackGround* ChapterBG = nullptr;
	Scene* TransitionActor = nullptr;
	Text* HeroActionPoint = nullptr;
	Hero* PlayerHero = nullptr;
	Demon* ChapterDemon = nullptr;

	static bool IsLoad;
};

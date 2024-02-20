#pragma once

#include "ContentsHelper.h"

#include <vector>
#include <set>

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

// Ό³Έν :
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
	void M_SpawnDemon(Point _Point, std::string_view _Name);
	void M_SpawnSkeleton(Point _Point);
	void M_SpawnStone(Point _Point, std::string_view _Name);
	void M_SpawnThorn(Point _Point, EThornState _State);
	void M_SpawnKey(Point _Point);
	void M_SetIsThornChange(bool _Value)
	{
		IsThornChange = _Value;
	}

	HitActor* M_GetHitActor(FVector _Point);
	HitActor* M_GetHitActor(Point _Point);
	void M_DestroyHitActor(__int64 _HitActor);
	void M_ChangeThornState();
	void M_UpdateHeroActionPoint();

	void M_SetChapterStartLocation(FVector _Value);
	FVector M_GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	void M_SetChapterEndPoint(Point _Point);

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
	
	// Debug
	void ShowLocationPoint();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	virtual void CutSceneStart();
	virtual void ChangeChapter() {};
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

	FVector ChapterStartLocation = FVector::Zero;
	Point EndPoint = { -1, -1 };
	int ChapterEndOrder = -1;

	int ChapterNumber = -1;
	int ChapterWidth = -1;
	int ChapterHeight = -1;
	bool IsThornChange = false;

	const float TransitionInter = 0.0435f;
	BackGround* ChapterBG = nullptr;
	Scene* TransitionActor = nullptr;
	Text* HeroActionPoint = nullptr;
	Hero* PlayerHero = nullptr;
	Demon* ChapterDemon = nullptr;
	Text* BottomText = nullptr;

	Point KeyPoint = { -1, -1 };
	Point KeyBoxPoint = { -1, -1 };

	EChapterState State = EChapterState::None;

	static bool IsLoad;
	static std::set<std::string> ChapterSet;
};

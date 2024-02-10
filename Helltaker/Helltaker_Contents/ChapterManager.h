#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>

class HitActor;
class Hero;

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
	
	void SetChapterStartLocation(FVector _Point);
	FVector GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	const std::vector<std::vector<bool>>& GetChapterVec() const
	{
		if (false == IsChapterVecInit)
		{
			MsgBoxAssert("ChapterMap Not Exist.");
		}

		return ChapterVec;
	}

	std::vector<std::vector<HitActor*>>& GetMoveActorVec()
	{
		if (false == IsChapterVecInit)
		{
			MsgBoxAssert("ChapterMap Not Exist.");
		}

		return HitActorVec;
	}

	void CreateChapterVec(const std::vector<std::vector<bool>>& _Map);
	void CreateMoveActorVec();
	
	void CreateBG(std::string_view _Name);
	void CreateChapterUI();
	void CreateHero(int _X, int _Y);
	void CreateSkeleton(int _X, int _Y);

	//void RestartChatper();

	HitActor* GetMoveActor(FVector _Point);
	HitActor* GetMoveActor(int _X, int _Y);

	// 디버그 용
	void ShowLocationPoint();

	void Tick(float _DeltaTime) override;

protected:

private:
	FVector ChapterStartLocation = FVector::Zero;

	int Width = -1;
	int Height = -1;

	std::vector<std::vector<bool>> ChapterVec;
	std::vector<std::vector<HitActor*>> HitActorVec;

	//std::list<RenderActor*> AllActors;
	Hero* PlayerHero = nullptr;

	bool IsChapterVecInit = false;
};

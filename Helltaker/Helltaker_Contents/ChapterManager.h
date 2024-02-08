#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>


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

	FVector ChapterPointToLocation(FVector _Point) const;
	FVector ChapterPointToLocation(int _X, int _Y) const;
	
	void SetChapterStartLocation(FVector _Point);
	FVector GetChapterStartLocation() const
	{
		return ChapterStartLocation;
	}

	const std::vector<std::vector<bool>>& GetChapterMap() const
	{
		if (false == IsChapterMapInit)
		{
			MsgBoxAssert("ChapterMap Not Exist.");
		}

		return ChapterMap;
	}

	void CreateChapterMap(const std::vector<std::vector<bool>>& _Map);

	void ShowLocationPoint();

protected:

private:
	FVector ChapterStartLocation = FVector::Zero;

	int Width = -1;
	int Height = -1;

	std::vector<std::vector<bool>> ChapterMap;
	std::vector<std::vector<bool>> IsEmptyTile;

	bool IsChapterMapInit = false;
};

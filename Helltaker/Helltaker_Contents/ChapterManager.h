#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>


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

	void SetChapterStartLocation(FVector _Point);

	FVector ChapterPointToLocation(FVector _Point);
	FVector ChapterPointToLocation(int _X, int _Y);

	void CreateChapterMap(int _X, int _Y);

protected:

private:
	FVector ChapterStartLocation = FVector::Zero;

	std::vector<std::vector<bool>> ChapterMap;
	std::vector<std::vector<bool>> IsEmptyTile;
};

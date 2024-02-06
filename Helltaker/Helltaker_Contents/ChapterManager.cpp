#include "ChapterManager.h"

#include "ContentsHelper.h"

ChapterManager::ChapterManager()
{
}

ChapterManager::~ChapterManager()
{
}

void ChapterManager::SetChapterStartLocation(FVector _Point)
{
	ChapterStartLocation = _Point * ContentsHelper::GetOneTileWidth();
}

FVector ChapterManager::ChapterPointToLocation(FVector _Point)
{
	return ChapterPointToLocation(static_cast<int>(_Point.X), static_cast<int>(_Point.Y));
}

FVector ChapterManager::ChapterPointToLocation(int _X, int _Y)
{
	FVector Location = ChapterStartLocation;
	Location += FVector(_X, _Y) * ContentsHelper::GetOneTileWidth();
	return Location;
}

void ChapterManager::CreateChapterMap(int _X, int _Y)
{
	ChapterMap.reserve(_Y);
	for (int i = 0; i < ChapterMap.size(); i++)
	{
		ChapterMap[i].reserve(_X);
	}
}

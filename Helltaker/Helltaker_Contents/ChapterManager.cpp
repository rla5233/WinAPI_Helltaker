#include "ChapterManager.h"

#include "ContentsHelper.h"


#include "RenderActor.h"
#include <math.h>
#include <vector>

ChapterManager::ChapterManager()
{
}

ChapterManager::~ChapterManager()
{
}

void ChapterManager::SetChapterStartLocation(FVector _Point)
{
	ChapterStartLocation = _Point * ContentsHelper::GetTileScale();
}

FVector ChapterManager::ChapterPointToLocation(FVector _Point)
{
	return ChapterPointToLocation(_Point.iX(), _Point.iY());
}

FVector ChapterManager::ChapterPointToLocation(int _X, int _Y)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Location = ChapterStartLocation;
	Location += FVector(_X, _Y) * ContentsHelper::GetTileScale();
	Location += {fmod(WinScale.X, 19.0f), fmod(WinScale.Y, 10.8f)};
	return Location;
}

void ChapterManager::CreateChapterMap(int _X, int _Y)
{
	Width = _X; Height = _Y;
	//ChapterMap.reserve(Height);
	//for (int i = 0; i < Height; i++)
	//{
	//	ChapterMap[i].reserve(Width);
	//}
}


// 디버그용
void ChapterManager::ShowLocationPoint()
{
	std::vector<std::vector<RenderActor*>> GreenPoint;
	
	GreenPoint.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		GreenPoint[i].resize(Width);
	}
	
	for (int Y = 0; Y < Height; Y++)
	{
		for (int X = 0; X < Width; X++)
		{
			GreenPoint[Y][X] = SpawnActor<RenderActor>(static_cast<int>(UpdateOrder::UI));
			GreenPoint[Y][X]->SetActorLocation(ChapterPointToLocation(X, Y));
			GreenPoint[Y][X]->CreateImageRenderer(RenderOrder::UI);
			GreenPoint[Y][X]->SetImg("GreenPoint.png");
			GreenPoint[Y][X]->SetTransform({ { 0,0 }, {2, 2} });
		}
	}
}

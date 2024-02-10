#include "ChapterManager.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Skeleton.h"
#include "Hero.h"
#include "UI.h"

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

FVector ChapterManager::ChapterPointToLocation(FVector _Point) const
{
	return ChapterPointToLocation(_Point.iX(), _Point.iY());
}

FVector ChapterManager::ChapterPointToLocation(int _X, int _Y) const
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Location = ChapterStartLocation;
	Location += FVector(_X, _Y) * ContentsHelper::GetTileScale();
	Location += {fmod(WinScale.X, 19.0f), fmod(WinScale.Y, 10.8f)};
	return Location;
}

void ChapterManager::CreateChapterMap(const std::vector<std::vector<bool>>& _Map)
{
	Width = static_cast<int>(_Map[0].size()); 
	Height = static_cast<int>(_Map.size());
	ChapterMap.resize(Height);
	for (int i = 0; i < Height; i++)
	{
		ChapterMap[i].resize(Width);
	}

	for (int Y = 0; Y < _Map.size(); Y++)
	{
		for (int X = 0; X < _Map[Y].size(); X++)
		{
			ChapterMap[Y][X] = _Map[Y][X];
		}
	}

	IsChapterMapInit = true;
}

void ChapterManager::CreateBG(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* ChapterBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	ChapterBG->CreateBackGround(_Name);
}

void ChapterManager::CreateChapterUI()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	UI* ChapterUI = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	ChapterUI->SetActorLocation(WinScale.Half2D());
	ChapterUI->SetName("ChapterUI");
	ChapterUI->LoadImg("UI");
	ChapterUI->CreateImageRenderer(RenderOrder::UI);
	ChapterUI->SetImg(ChapterUI->GetName() + ".png");
	ChapterUI->SetTransform({ {0,0}, WinScale });
}

void ChapterManager::CreateHero(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Hero* NewHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	NewHero->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewHero->SetLocationPoint({ _X, _Y });
}

void ChapterManager::CreateSkeleton(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::Skeleton));
	NewSkeleton->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewSkeleton->SetLocationPoint({ _X, _Y });
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
			
			if (ChapterMap[Y][X])
			{
				GreenPoint[Y][X]->SetImg("GreenPoint.png");
			}
			else
			{
				GreenPoint[Y][X]->SetImg("RedPoint.png");
			}
			
			GreenPoint[Y][X]->SetTransform({ { 0,0 }, {2, 2} });
		}
	}
}
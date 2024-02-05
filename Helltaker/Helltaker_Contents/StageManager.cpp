#include "StageManager.h"

#include "Hero.h"
#include "Skeleton.h"
#include "ContentsHelper.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

void StageManager::SetStageStartLocation(FVector _Point)
{
	StageStartLocation = _Point * ContentsHelper::GetOneTileWidth();
}

FVector StageManager::StagePointToLocation(FVector _Point)
{
	return StagePointToLocation(static_cast<int>(_Point.X), static_cast<int>(_Point.Y));
}

FVector StageManager::StagePointToLocation(int _X, int _Y)
{
	FVector Location = StageStartLocation;
	Location += FVector(_X, _Y) * ContentsHelper::GetOneTileWidth();
	return Location;
}

void StageManager::CreateStageMap(int _X, int _Y)
{
	StageMap.reserve(_Y);
	for (int i = 0; i < StageMap.size(); i++)
	{
		StageMap[i].reserve(_X);
	}
}

void StageManager::BeginPlay()
{
	ULevel::BeginPlay();
}

void StageManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}


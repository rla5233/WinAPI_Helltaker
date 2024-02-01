#include "StageManager.h"

#include "Hero.h"
#include "Skeleton.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>


const float StageManager::OneTileWidth = 70.0f;

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

FVector StageManager::StagePointToLocation(FVector _Point)
{
	return StagePointToLocation(static_cast<int>(_Point.X), static_cast<int>(_Point.Y));
}

FVector StageManager::StagePointToLocation(int _X, int _Y)
{
	FVector Location = StageStartLocation;
	Location += FVector(_X, _Y) * OneTileWidth;
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


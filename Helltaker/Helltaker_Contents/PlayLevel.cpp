#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"

#include <EngineBase/EnginePath.h>

UPlayLevel::UPlayLevel()
{}

UPlayLevel::~UPlayLevel()
{}


void UPlayLevel::BeginPlay()
{
	UEnginePath ResourcesPath = UEnginePath();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");

	SpawnActor<Player>();
	SpawnActor<Monster>();
}
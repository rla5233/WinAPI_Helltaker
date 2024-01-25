#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"

UPlayLevel::UPlayLevel()
{}

UPlayLevel::~UPlayLevel()
{}


void UPlayLevel::BeginPlay()
{
	SpawnActor<Player>();
	SpawnActor<Monster>();
}
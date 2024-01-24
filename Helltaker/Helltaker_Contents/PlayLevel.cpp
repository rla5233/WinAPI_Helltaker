#include "PlayLevel.h"
#include "Player.h"

UPlayLevel::UPlayLevel()
{}

UPlayLevel::~UPlayLevel()
{}


void UPlayLevel::BeginPlay()
{
	SpawnActor<Player>();

	// SpawnActor<Player>();

	// 할일은 
	// 플레이어
	// 배경
	// 몬스터
	// 등등등을 코드로 여기서 다 만들어야 한다.
}
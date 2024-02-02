#include "MoveActor.h"
#include "StageManager.h"

#include <EnginePlatform/EngineInput.h>

MoveActor::MoveActor()
{
	MoveDistance = StageManager::GetOneTileWidth();
}

MoveActor::~MoveActor()
{}

void MoveActor::MoveCheck(float _DeltaTime)
{
	if (false == IsMoving)
	{
		if (true == EngineInput::IsPress('A'))
		{
			MoveDir = FVector::Left;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('D'))
		{
			MoveDir = FVector::Right;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('W'))
		{
			MoveDir = FVector::Up;
			IsMoving = true;
		}

		if (true == EngineInput::IsPress('S'))
		{
			MoveDir = FVector::Down;
			IsMoving = true;
		}
	}
}

void MoveActor::MoveOneBlock(float _DeltaTime)
{
	if (true == IsMoving)
	{

		if (0 < MoveDistance)
		{
			AddActorLocation(MoveDir * Speed * _DeltaTime);
			MoveDistance -= Speed * _DeltaTime;
		}
		else
		{
			LocationPoint += MoveDir;
			float hTileWidth = StageManager::GetOneTileWidth() / 2;
			FVector hTile = { hTileWidth , hTileWidth };
			SetActorLocation(dynamic_cast<StageManager*>(GetWorld())->StagePointToLocation(LocationPoint) + hTile);
			MoveDistance = StageManager::GetOneTileWidth();
			IsMoving = false;
		}
	}
}
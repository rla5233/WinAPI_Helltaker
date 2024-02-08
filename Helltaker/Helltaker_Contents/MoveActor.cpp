#include "MoveActor.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

#include <EnginePlatform/EngineInput.h>

MoveActor::MoveActor()
{
	MoveDistance = ContentsHelper::GetOneTileWidth();
}

MoveActor::~MoveActor()
{}

void MoveActor::MoveCheck(float _DeltaTime)
{
	if (false == IsMoving)
	{
		if (EngineInput::IsPress('A') || EngineInput::IsPress(VK_LEFT))
		{
			MoveDir = FVector::Left;
			IsMoving = true;
		}
		else if (EngineInput::IsPress('D') || EngineInput::IsPress(VK_RIGHT))
		{
			MoveDir = FVector::Right;
			IsMoving = true;
		}
		else if (EngineInput::IsPress('W') || EngineInput::IsPress(VK_UP))
		{
			MoveDir = FVector::Up;
			IsMoving = true;
		}
		else if (EngineInput::IsPress('S') || EngineInput::IsPress(VK_DOWN))
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
			float hTileWidth = ContentsHelper::GetOneTileWidth() / 2;
			FVector hTile = { hTileWidth , hTileWidth };
			SetActorLocation(dynamic_cast<ChapterManager*>(GetWorld())->ChapterPointToLocation(LocationPoint) + hTile);
			MoveDistance = ContentsHelper::GetOneTileWidth();
			IsMoving = false;
		}
	}
}
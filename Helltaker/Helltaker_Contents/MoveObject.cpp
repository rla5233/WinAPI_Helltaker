#include "MoveObject.h"
#include "StageManager.h"

#include <EnginePlatform/EngineInput.h>

MoveObject::MoveObject()
{
	MoveDistance = StageManager::GetOneTileDistance();
}

MoveObject::~MoveObject()
{
}

void MoveObject::MoveCheck(float _DeltaTime)
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

void MoveObject::MoveOneBlock(float _DeltaTime)
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
			//AddActorLocation(MoveDir * MoveDistance);
			MoveDistance += StageManager::GetOneTileDistance();
			IsMoving = false;
		}
	}
}
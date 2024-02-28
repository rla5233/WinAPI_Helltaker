#include "Character.h"

#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

Character::Character()
{
}

Character::~Character()
{
}

void Character::CreateImageRenderer(RenderOrder _Order)
{
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

void Character::CreateNameRenderer(RenderOrder _Order)
{
	NameRenderer = RenderActor::CreateImageRenderer(_Order);
}

void Character::ImageRendererMoveUpdate(float _DeltaTime, float _TimeWeight/* = 1.0f */)
{
	if (true == IsImageMoveValue)
	{
		MoveTime += _DeltaTime * _TimeWeight;

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		ImageRenderer->SetPosition(NextPos);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsImageMoveValue = false;
		}
	}
}
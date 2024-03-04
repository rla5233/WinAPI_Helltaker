#include "SinMoveActor.h"

SinMoveActor::SinMoveActor()
{
}

SinMoveActor::~SinMoveActor()
{
}

void SinMoveActor::LerfMoveUpdate(float _DeltaTime, float _TimeWeight /* = 1.0f */)
{
	if (true == IsLerfMove)
	{
		LerfMoveTime += _DeltaTime * _TimeWeight;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, LerfMoveTime);
		SetActorLocation(NextPos);

		if (1.0f <= LerfMoveTime)
		{
			LerfMoveTime = 0.0f;
			IsLerfMove = false;
		}
	}
}

void SinMoveActor::MoveY_Update(float _Speed, float _DeltaTime)
{
	if (true == IsMove)
	{
		AddActorLocation({ 0.0f, _Speed * _DeltaTime });

		if (EndPosY >= GetActorLocation().Y)
		{
			float Diff = GetActorLocation().Y - EndPosY;
			SetActorLocation({ GetActorLocation().X, ResetPosY + Diff });
		}
	}
}

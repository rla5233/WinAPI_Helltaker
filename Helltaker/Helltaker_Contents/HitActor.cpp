#include "HitActor.h"

#include "ChapterManager.h"

HitActor::HitActor()
{
}

HitActor::HitActor(float _Speed, float _Acceleration)
	: MoveActor(_Speed, _Acceleration)
{
}

HitActor::~HitActor()
{
}

void HitActor::HitActorVecUpdate(EHitActorState _NextState)
{
	FVector CurPoint = GetLocationPoint();
	FVector NextPoint = GetNextLocationPoint();

	switch (_NextState)
	{
	case EHitActorState::Hit:
		GetChapter()->GetMoveActorVec()[CurPoint.iY()][CurPoint.iX()] = nullptr;
		GetChapter()->GetMoveActorVec()[NextPoint.iY()][NextPoint.iX()] = this;
		break;
	case EHitActorState::Death:
		GetChapter()->GetMoveActorVec()[CurPoint.iY()][CurPoint.iX()] = nullptr;
		break;
	default:
		break;
	}	
}

void HitActor::CallDestroy()
{
	GetChapter()->DestroyHitActor(reinterpret_cast<__int64>(this));
}

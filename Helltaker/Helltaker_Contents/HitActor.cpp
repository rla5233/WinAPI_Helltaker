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

void HitActor::HitActorInfoUpdate(EHitActorState _NextState)
{
	FVector CurPoint = GetLocationPoint();
	FVector NextPoint = GetNextLocationPoint();

	switch (_NextState)
	{
	case EHitActorState::Hit:
		GetChapter()->M_SetChapterHitAcotrInfo(CurPoint.iX(), CurPoint.iY(), nullptr);
		GetChapter()->M_SetChapterHitAcotrInfo(NextPoint.iX(), NextPoint.iY(), this);
		break;
	case EHitActorState::Death:
		GetChapter()->M_SetChapterHitAcotrInfo(CurPoint.iX(), CurPoint.iY(), nullptr);
		break;
	default:
		break;
	}	
}

void HitActor::CallDestroytoChapter()
{
	GetChapter()->DestroyHitActor(reinterpret_cast<__int64>(this));
}

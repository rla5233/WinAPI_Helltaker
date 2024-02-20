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
	Point CurPoint = GetLocationPoint();
	Point NextPoint = GetNextLocationPoint();

	switch (_NextState)
	{
	case EHitActorState::Hit:
		GetChapter()->M_SetChapterHitAcotrInfo(CurPoint, nullptr);
		GetChapter()->M_SetChapterHitAcotrInfo(NextPoint, this);
		break;
	case EHitActorState::Death:
		GetChapter()->M_SetChapterHitAcotrInfo(CurPoint, nullptr);
		break;
	default:
		break;
	}	
}

void HitActor::InformDestroytoChapter()
{
	GetChapter()->M_DestroyHitActor(reinterpret_cast<__int64>(this));
}

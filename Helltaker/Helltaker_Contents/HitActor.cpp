#include "HitActor.h"

#include "ChapterManager.h"

bool HitActor::IsLoad = false;
const float HitActor::BigHitInter = 0.04f;
const float HitActor::SmallHitInter = 0.02f;

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

void HitActor::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Effect", "Hit");

		IsLoad = true;
	}
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
	}	
}

void HitActor::InformDestroytoChapter()
{
	GetChapter()->M_DestroyHitActor(reinterpret_cast<__int64>(this));
}

void HitActor::CreateBigHitEffect()
{
	EffectRenderer = CreateImageRenderer(RenderOrder::Effect);
	EffectRenderer->SetImage("Hit");
	EffectRenderer->CreateAnimation("BigHit1", "Hit", 0, 4, BigHitInter, false);
	EffectRenderer->CreateAnimation("BigHit2", "Hit", 5, 9, BigHitInter, false);
}

void HitActor::CreateSmallHitEffect()
{
	EffectRenderer = CreateImageRenderer(RenderOrder::Effect);
	EffectRenderer->SetImage("Hit");
	EffectRenderer->CreateAnimation("SmallHit1", "Hit", 10, 13, SmallHitInter, false);
	EffectRenderer->CreateAnimation("SmallHit2", "Hit", 14, 17, SmallHitInter, false);
}

void HitActor::SetRandomBigHitEffect()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	EffectRenderer->AnimationReset();
	EffectRenderer->ChangeAnimation("BigHit1");
	EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.081f, WinScale.Y * 0.186f } });
	EffectRenderer->ActiveOn();
}

void HitActor::HitEffectOffCheck()
{
	if (true == EffectRenderer->IsCurAnimationEnd())
	{
		EffectRenderer->ActiveOff();
	}
}

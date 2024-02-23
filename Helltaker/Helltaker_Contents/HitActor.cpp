#include "HitActor.h"

#include "ChapterManager.h"

bool HitActor::IsLoad = false;
const float HitActor::BigHitInter = 0.04f;
const float HitActor::SmallHitInter = 0.04f;

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
	MoveActor::BeginPlay();

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
	case EHitActorState::Move:
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
	EffectRenderer->AnimationReset();
}

void HitActor::SetRandomBigHitEffect()
{
	int RandomValue = rand() % 2;

	FVector WinScale = ContentsHelper::GetWindowScale();
	EffectRenderer->AnimationReset();
	switch (RandomValue)
	{
	case 0:
		EffectRenderer->ChangeAnimation("BigHit1");
		EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.081f, WinScale.Y * 0.186f } });
		break;
	case 1:
		EffectRenderer->ChangeAnimation("BigHit2");
		EffectRenderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.09f, WinScale.Y * 0.145f } });
		break;
	}
	
	EffectRenderer->ActiveOn();
}

void HitActor::SetRandomSmallHitEffect()
{
	int RandomValue = rand() % 2;			// 0 ~ 1
	int RandomValueX = (rand() % 10) - 4;	// -4 ~ 5
	int RandomValueY = (rand() % 10) - 4;	// -4 ~ 5

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector RandomPos = { WinScale.X * (RandomValueX * 0.002f + 0.002f), WinScale.Y * (RandomValueY * 0.002f - 0.015f)};
	EffectRenderer->AnimationReset();
	switch (RandomValue)
	{
	case 0:
		EffectRenderer->ChangeAnimation("SmallHit1");
		EffectRenderer->SetTransform({ RandomPos, { WinScale.X * 0.04f, WinScale.Y * 0.074f } });
		break;
	case 1:
		EffectRenderer->ChangeAnimation("SmallHit2");
		EffectRenderer->SetTransform({ RandomPos, { WinScale.X * 0.047f, WinScale.Y * 0.076f } });
		break;
	}

	EffectRenderer->ActiveOn();
}

bool HitActor::HitEffectEndCheck()
{
	if (nullptr == EffectRenderer->GetCurAnimation())
	{
		return false;
	}

	if (true == EffectRenderer->IsCurAnimationEnd())
	{
		EffectRenderer->ActiveOff();
		return true;
	}

	return false;
}

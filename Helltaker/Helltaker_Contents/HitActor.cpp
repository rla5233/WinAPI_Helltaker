#include "HitActor.h"

#include "ChapterManager.h"

bool HitActor::IsLoad = false;
const float HitActor::BigHitInter = 0.04f;
const float HitActor::SmallHitInter = 0.04f;

HitActor::HitActor()
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

void HitActor::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	HitEffectEndCheck();
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

void HitActor::CreateRandomBigHitEffect()
{
	UImageRenderer*	Renderer = CreateImageRenderer(RenderOrder::Effect);
	Renderer->SetImage("Hit");

	int RandomValue = rand() % 2;

	FVector WinScale = ContentsHelper::GetWindowScale();
	switch (RandomValue)
	{
	case 0 :
		Renderer->CreateAnimation("BigHit1", "Hit", 0, 4, BigHitInter, false);
		Renderer->ChangeAnimation("BigHit1");
		Renderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.081f, WinScale.Y * 0.186f } });
		break;
	case 1:
		Renderer->CreateAnimation("BigHit2", "Hit", 5, 9, BigHitInter, false);
		Renderer->ChangeAnimation("BigHit2");
		Renderer->SetTransform({ { 0, 0 }, { WinScale.X * 0.09f, WinScale.Y * 0.145f } });
		break;
	}

	AllHitEffectRenderer.push_back(Renderer);
}

void HitActor::CreateRandomSmallHitEffect()
{
	UImageRenderer* Renderer = CreateImageRenderer(RenderOrder::Effect);
	Renderer->SetImage("Hit");

	int RandomValue = rand() % 2;
	int RandomValueX = (rand() % 10) - 4;	// -4 ~ 5
	int RandomValueY = (rand() % 10) - 4;	// -4 ~ 5
	
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector RandomPos = { WinScale.X * (RandomValueX * 0.002f + 0.002f), WinScale.Y * (RandomValueY * 0.002f - 0.015f)};
	switch (RandomValue)
	{
	case 0 :
		Renderer->CreateAnimation("SmallHit1", "Hit", 28, 31, SmallHitInter, false);
		Renderer->ChangeAnimation("SmallHit1");
		Renderer->SetTransform({ RandomPos, { WinScale.X * 0.04f, WinScale.Y * 0.074f } });
		break;
	case 1:
		Renderer->CreateAnimation("SmallHit2", "Hit", 32, 35, SmallHitInter, false);
		Renderer->ChangeAnimation("SmallHit2");
		Renderer->SetTransform({ RandomPos, { WinScale.X * 0.047f, WinScale.Y * 0.076f } });
		break;
	}

	AllHitEffectRenderer.push_back(Renderer);
}

bool HitActor::AllEffectEndCheck()
{
	return HitEffectEndCheck() && MoveEffectEndCheck();
}

bool HitActor::HitEffectEndCheck()
{
	if (true == AllHitEffectRenderer.empty())
	{
		return true;
	}

	if (true == AllHitEffectRenderer.front()->IsCurAnimationEnd())
	{
		AllHitEffectRenderer.front()->ActiveOff();
		AllHitEffectRenderer.front()->Destroy();
		AllHitEffectRenderer.pop_front();
	}

	return false;
}

void HitActor::EffectPosUpdate(const FVector& _Diff)
{
	MoveActor::EffectPosUpdate(_Diff);

	for (UImageRenderer* Renderer : AllHitEffectRenderer)
	{
		if (nullptr == Renderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		FVector CurPos = Renderer->GetPosition();
		Renderer->SetPosition(CurPos - _Diff);
	}
}

void HitActor::AddHitEffectRenderer(UImageRenderer* const _Renderer)
{
	AllHitEffectRenderer.push_back(_Renderer);
}
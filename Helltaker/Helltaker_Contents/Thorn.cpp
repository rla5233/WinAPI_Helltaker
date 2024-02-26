#include "Thorn.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"
#include "Skeleton.h"

bool Thorn::IsLoad = false;

const FVector Thorn::IdleScale = { 0.048f, 0.085f };
const float Thorn::ChangeInter = 0.05f;

Thorn::Thorn()
{
}

Thorn::~Thorn()
{
}

void Thorn::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

		IsLoad = true;
	}

	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer = CreateImageRenderer(RenderOrder::RenderActor);
	ImageRenderer->SetImage("Thorn_Idle.png");
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * 0.018f }, { WinScale * IdleScale } });
	ImageRenderer->CreateAnimation("Thorn_Up", "Thorn_Up", 0, 3, ChangeInter, false);
	ImageRenderer->CreateAnimation("Thorn_Down", "Thorn_Down", 0, 4, ChangeInter, false);
}

void Thorn::Idle(float _DeltaTime)
{
}

void Thorn::IdleStart()
{
}

void Thorn::Up(float _DeltaTime)
{
	if (3 == ImageRenderer->GetCurAnimationFrame())
	{
		Skeleton* Skel = dynamic_cast<Skeleton*>(GetChapter()->M_GetHitActor(ThornPoint));
		if (nullptr != Skel)
		{
			Skel->ThornHitCheck();
		}
	}
}

void Thorn::UpStart()
{
	ImageRenderer->ChangeAnimation("Thorn_Up");		
	GetChapter()->M_SetChapterThornInfo(ThornPoint, true);
}

void Thorn::Down(float _DeltaTime)
{
}

void Thorn::DownStart()
{
	ImageRenderer->ChangeAnimation("Thorn_Down");
	GetChapter()->M_SetChapterThornInfo(ThornPoint, false);
}

void Thorn::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Thorn::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EThornState::Idle:
		Idle(_DeltaTime);
		break;
	case EThornState::Up:
		Up(_DeltaTime);
		break;
	case EThornState::Down:
		Down(_DeltaTime);
		break;
	}
}

void Thorn::StateChange(EThornState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EThornState::Idle:
			IdleStart();
			break;
		case EThornState::Up:
			UpStart();
			break;
		case EThornState::Down:
			DownStart();
			break;
		}
	}

	State = _State;
}
#include "HeroBase.h"

#include "ChapterManager.h"

bool HeroBase::IsLoad = false;

const FVector HeroBase::HitScale = { 0.092f, 0.1185f };
const float HeroBase::HitInter = 0.08f;

const FVector HeroBase::IdleScale = { 0.052f, 0.083f };
const float HeroBase::IdleInter = 0.057f;

const FVector HeroBase::MoveScale = { 0.047f, 0.083f };
const float HeroBase::MoveInter = 0.03f;

const FVector HeroBase::KickScale = { 0.049f, 0.088f };
const float HeroBase::KickInter = 0.06f;

const float HeroBase::DeathInter = 0.05f;

const FVector HeroBase::VictoryScale = { 0.052f, 0.111f };
const float HeroBase::VictoryInter = 0.125f;


HeroBase::HeroBase()
{}

HeroBase::~HeroBase()
{}

void HeroBase::BeginPlay()
{
	HitActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Idle");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Move");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Kick");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Left_Victory");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Idle");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Move");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Kick");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Right_Victory");
		ContentsHelper::LoadFolder("Chapter\\Hero", "Hero_Death");

		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(RenderOrder::Hero);

	ImageRenderer->SetImage("Hero_Left_Idle");
	ImageRenderer->CreateAnimation("Hero_LIdle", "Hero_Left_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Hero_LMove", "Hero_Left_Move", 0, 5, MoveInter, false);
	ImageRenderer->CreateAnimation("Hero_LKick", "Hero_Left_Kick", 0, 12, KickInter, false);
	ImageRenderer->CreateAnimation("Hero_LVictory", "Hero_Left_Victory", 0, 31, VictoryInter, false);

	ImageRenderer->CreateAnimation("Hero_RIdle", "Hero_Right_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Hero_RMove", "Hero_Right_Move", 0, 5, MoveInter, false);
	ImageRenderer->CreateAnimation("Hero_RKick", "Hero_Right_Kick", 0, 12, KickInter, false);
	ImageRenderer->CreateAnimation("Hero_RVictory", "Hero_Right_Victory", 0, 31, VictoryInter, false);

	ImageRenderer->CreateAnimation("Hero_Death", "Hero_Death", 0, 17, DeathInter, false);

	SeeDirChange(EActorSeeDir::Right);
}

void HeroBase::InputCheck(float _DeltaTime)
{
	if (false == CanActionCheck)
	{
		return;
	}

	if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
	{
		MoveDirChange(EMoveActorDir::Up);
		ActionCheck(_DeltaTime, 'W', VK_UP);
	}
	else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
	{
		MoveDirChange(EMoveActorDir::Left);
		SeeDirChange(EActorSeeDir::Left);
		ActionCheck(_DeltaTime, 'A', VK_LEFT);
	}
	else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
	{
		MoveDirChange(EMoveActorDir::Down);
		ActionCheck(_DeltaTime, 'S', VK_DOWN);
	}
	else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
	{
		MoveDirChange(EMoveActorDir::Right);
		SeeDirChange(EActorSeeDir::Right);
		ActionCheck(_DeltaTime, 'D', VK_RIGHT);
	}

	// Debug
	if (UEngineInput::IsPress('K'))
	{
		StateChange(EHeroState::Death);
	}
	else if (UEngineInput::IsDown('C'))
	{
		CheatMode = !CheatMode;
	}
}

void HeroBase::CreateRandomHitEffect()
{
	UImageRenderer* Renderer = CreateImageRenderer(RenderOrder::Effect);
	Renderer->SetImage("Hit");

	int RandomValue = rand() % 3;

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector TransPos = { WinScale.X * 0.005f, WinScale.Y * (-0.08f) };
	switch (RandomValue)
	{
	case 0:
		Renderer->CreateAnimation("HeroHit1", "Hit", 10, 15, HitInter, false);
		Renderer->ChangeAnimation("HeroHit1");
		Renderer->SetTransform({ TransPos, { WinScale * HitScale } });
		break;
	case 1:
		Renderer->CreateAnimation("HeroHit2", "Hit", 16, 21, HitInter, false);
		Renderer->ChangeAnimation("HeroHit2");
		Renderer->SetTransform({ TransPos, { WinScale * HitScale } });
		break;
	case 2:
		Renderer->CreateAnimation("HeroHit3", "Hit", 22, 27, HitInter, false);
		Renderer->ChangeAnimation("HeroHit3");
		Renderer->SetTransform({ TransPos, { WinScale * HitScale } });
		break;
	}

	AddHitEffectRenderer(Renderer);
}

void HeroBase::Idle(float _DeltaTime)
{
	InputCheck(_DeltaTime);
}

void HeroBase::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.01f) }, { WinScale * IdleScale } });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Hero_LIdle");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Hero_RIdle");
		break;
	}
}

void HeroBase::Move(float _DeltaTime)
{
	InputCheck(_DeltaTime);

	MoveOneBlock(_DeltaTime);

	if ((false == IsMove()) && (true == ImageRenderer->IsCurAnimationEnd()))
	{
		StateChange(EHeroState::Idle);
	}
}

void HeroBase::MoveStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.01f) }, { WinScale * MoveScale } });
	CanActionCheck = false;

	GetChapter()->M_ChangeThornState();

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_LMove");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_RMove");
		break;
	}

	HitActor::MoveStart();
}

void HeroBase::Kick(float _DeltaTime)
{
	InputCheck(_DeltaTime);

	if (true == ImageRenderer->IsCurAnimationEnd())
	{
		StateChange(EHeroState::Idle);
		return;
	}

	if (2 == ImageRenderer->GetCurAnimationImageFrame())
	{
		switch (SeeDir)
		{
		case EActorSeeDir::Left:
			ImageRenderer->AnimationReset();
			ImageRenderer->ChangeAnimation("Hero_LKick", false, 3);
			break;
		case EActorSeeDir::Right:
			ImageRenderer->AnimationReset();
			ImageRenderer->ChangeAnimation("Hero_RKick", false, 3);
			break;
		}

		KickCheck();
	}
}

void HeroBase::KickStart(float _DeltaTime, int _Key1, int _Key2)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	CanActionCheck = false;

	GetChapter()->M_ChangeThornState();

	Point NextPoint = GetNextLocationPoint();
	HitActor* Other = GetChapter()->M_GetHitActor(NextPoint);
	Other->NextStateCheck(MoveDir);

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_LKick");
		ImageRenderer->SetTransform({ { WinScale.X * 0.001f, WinScale.Y * (-0.011f) }, { WinScale * KickScale } });
		break;
	case EActorSeeDir::Right:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Hero_RKick");
		ImageRenderer->SetTransform({ { WinScale.X * (-0.001f), WinScale.Y * (-0.011f) }, { WinScale * KickScale } });
		break;
	}
}

void HeroBase::Victory(float _DeltaTime)
{
}

void HeroBase::VictoryStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.0225f) }, { WinScale * VictoryScale } });
	AllEffectActiveOff();

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Hero_LVictory");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Hero_RVictory");
		break;
	}
}

void HeroBase::AllEffectActiveOff()
{
	AllHitEffectActiveOff();
	AllMoveEffectActiveOff();
}

void HeroBase::Death(float _DeltaTime)
{
}

void HeroBase::DeathStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ {0.0f, (WinScale.Y * 1.15f) * (-0.25f)}, {WinScale.X * 0.375f, WinScale.Y * 1.15f} });
	ImageRenderer->ChangeAnimation("Hero_Death");
}

void HeroBase::Tick(float _DeltaTime)
{
	HitActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void HeroBase::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EHeroState::Idle:
		Idle(_DeltaTime);
		break;
	case EHeroState::Move:
		Move(_DeltaTime);
		break;
	case EHeroState::Kick:
		Kick(_DeltaTime);
		break;
	case EHeroState::Victory:
		Victory(_DeltaTime);
		break;
	case EHeroState::Death:
		Death(_DeltaTime);
		break;
	}
}

void HeroBase::StateChange(EHeroState _State, float _DeltaTime, int _Key1, int _Key2)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EHeroState::Idle:
			IdleStart();
			break;
		case EHeroState::Move:
			MoveStart();
			break;
		case EHeroState::Kick:
			KickStart(_DeltaTime, _Key1, _Key2);
			break;
		case EHeroState::Victory:
			VictoryStart();
			break;
		case EHeroState::Death:
			DeathStart();
			break;
		}
	}

	State = _State;
}
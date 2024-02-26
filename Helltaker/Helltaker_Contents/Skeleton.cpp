#include "Skeleton.h"

#include "ChapterManager.h"

bool Skeleton::IsLoad = false;
const FVector Skeleton::IdleScale = { 0.047f, 0.083f };
const float Skeleton::IdleInter = 0.06f;

const FVector Skeleton::HitScale = { 0.0494f, 0.083f };
const float Skeleton::HitInter = 0.04f;

const FVector DeathParticle::Scale = { 0.021f, 0.022f };

Skeleton::Skeleton()
{}

Skeleton::~Skeleton()
{}

void Skeleton::BeginPlay()
{
	HitActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Left_Idle");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Right_Idle");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Left_Hit");
		ContentsHelper::LoadFolder("Chapter\\Skeleton", "Skeleton_Right_Hit");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_001.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_002.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_003.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_004.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_005.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_006.png");
		ContentsHelper::LoadImg("Effect\\Particle", "Skel_Particle_007.png");
		
		IsLoad = true;
	}

	ImageRenderer = CreateImageRenderer(RenderOrder::HitActor);
	ImageRenderer->SetImage("Skeleton_Left_Idle");
	ImageRenderer->CreateAnimation("Skeleton_LIdle", "Skeleton_Left_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Skeleton_RIdle", "Skeleton_Right_Idle", 0, 11, IdleInter, true);
	ImageRenderer->CreateAnimation("Skeleton_LHit", "Skeleton_Left_Hit", 0, 8, HitInter, false);
	ImageRenderer->CreateAnimation("Skeleton_RHit", "Skeleton_Right_Hit", 0, 8, HitInter, false);

	SeeDirChange(EActorSeeDir::Right);
	StateChange(EHitActorState::Idle);
}

// 수정 (Stone, HitActor virtual 관계 리팩토링 가능?)
void Skeleton::NextStateCheck(EMoveActorDir _OtherMoveDir)
{
	HitActor::NextStateCheck(_OtherMoveDir);

	const std::vector<std::vector<TileInfo>>& Map = GetChapter()->GetTileInfoVec();
	Point CurPoint = GetLocationPoint();

	switch (_OtherMoveDir)
	{
	case EMoveActorDir::Left:
		SeeDirChange(EActorSeeDir::Right);
		MoveDirChange(EMoveActorDir::Left);
		break;
	case EMoveActorDir::Right:
		SeeDirChange(EActorSeeDir::Left);
		MoveDirChange(EMoveActorDir::Right);
		break;
	case EMoveActorDir::Up:
		MoveDirChange(EMoveActorDir::Up);
		break;
	case EMoveActorDir::Down:
		MoveDirChange(EMoveActorDir::Down);
		break;
	}

	switch (MoveDir)
	{
	case EMoveActorDir::Left:
		SetNextLocationPoint(CurPoint + Point::Left);
		break;
	case EMoveActorDir::Right:
		SetNextLocationPoint(CurPoint + Point::Right);
		break;
	case EMoveActorDir::Up:
		SetNextLocationPoint(CurPoint + Point::Up);
		break;
	case EMoveActorDir::Down:
		SetNextLocationPoint(CurPoint + Point::Down);
		break;
	}

	int Height = static_cast<int>(Map.size());
	int Width = static_cast<int>(Map[0].size());
	Point NextPoint = GetNextLocationPoint();
	if (0 <= NextPoint.Y && NextPoint.Y < Height && 0 <= NextPoint.X && NextPoint.X < Width)
	{
		if (true == Map[NextPoint.Y][NextPoint.X].IsVaild)
		{
			NextTileCheck(NextPoint);
			return;
		}
	}

	StateChange(EHitActorState::Death);
}

void Skeleton::NextTileCheck(Point _Point)
{
	if (nullptr == GetChapter()->M_GetHitActor(_Point))
	{
		StateChange(EHitActorState::Hit);
	}
	else
	{
		StateChange(EHitActorState::Death);
	}	
}

void Skeleton::Idle(float _DeltaTime)
{
	Point CurPoint = GetLocationPoint();
	if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
	{
		StateChange(EHitActorState::Death);
	}
}

void Skeleton::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.012f) }, { WinScale * IdleScale }});

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->ChangeAnimation("Skeleton_LIdle");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->ChangeAnimation("Skeleton_RIdle");
		break;
	}
}

void Skeleton::Move(float _DeltaTime)
{
	MoveOneBlock(_DeltaTime);

	if (false == IsMove())
	{
		Point CurPoint = GetLocationPoint();
		if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
		{
			StateChange(EHitActorState::Death);
			return;
		}

		if (true == ImageRenderer->IsCurAnimationEnd())
		{
			StateChange(EHitActorState::Idle);
		}
	}
}

void Skeleton::MoveStart()
{
	MoveActor::MoveStart();

	HitActorInfoUpdate(EHitActorState::Move);
}

void Skeleton::Hit(float _DeltaTime)
{
	StateChange(EHitActorState::Move);
}

void Skeleton::HitStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.012f) }, { WinScale * HitScale } });

	switch (SeeDir)
	{
	case EActorSeeDir::Left:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Skeleton_LHit");
		break;
	case EActorSeeDir::Right:
		ImageRenderer->AnimationReset();
		ImageRenderer->ChangeAnimation("Skeleton_RHit");
		break;
	}

	CreateRandomBigHitEffect();
}

void Skeleton::Death(float _DeltaTime)
{
	if (true == HitEffectEndCheck())
	{
		Destroy();	
	}
}

void Skeleton::DeathStart()
{
	CreateRandomBigHitEffect();
	ImageRenderer->ActiveOff();

	for (int i = 0; i < 14; i++)
	{
		CreateRandomDeathParicle();
	}

	HitActorInfoUpdate(EHitActorState::Death);
	InformDestroytoChapter();
}

void Skeleton::CreateRandomDeathParicle()
{
	// 14개 파티클 랜덤인듯
	DeathParticle NewDeathParticle = DeathParticle();
	NewDeathParticle.DeathParticleRenderer = CreateImageRenderer(RenderOrder::Effect);

	int RandomValue = (rand() % 7) + 1;
	std::string Name = "Skel_Particle_00";
	Name += RandomValue + '0';
	Name += ".png";

	FVector WinScale = ContentsHelper::GetWindowScale();
	NewDeathParticle.DeathParticleRenderer->SetImage(Name);
	NewDeathParticle.DeathParticleRenderer->SetTransform({ {0, 0}, WinScale * DeathParticle::Scale });

	AllDeathParticle.push_back(NewDeathParticle);
}

void Skeleton::Tick(float _DeltaTime)
{
	HitActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Skeleton::StateUpdate(float _DeltaTime)
{
	switch (GetHitActorState())
	{
	case EHitActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EHitActorState::Hit:
		Hit(_DeltaTime);
		break;
	case EHitActorState::Move:
		Move(_DeltaTime);
		break;
	case EHitActorState::Death:
		Death(_DeltaTime);
		break;
	}
}

void Skeleton::StateChange(EHitActorState _State)
{
	if (GetHitActorState() != _State)
	{
		switch (_State)
		{
		case EHitActorState::Idle:
			IdleStart();
			break;
		case EHitActorState::Hit:
			HitStart();
			break;
		case EHitActorState::Move:
			MoveStart();
			break;
		case EHitActorState::Death:
			DeathStart();
			break;
		}
	}

	SetHitActorState(_State);
}
#include "Skeleton.h"

#include "ChapterManager.h"

#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineSound.h>

bool Skeleton::IsLoad = false;
const FVector Skeleton::IdleScale = { 0.047f, 0.083f };
const float Skeleton::IdleInter = 0.06f;

const FVector Skeleton::HitScale = { 0.0494f, 0.083f };
const float Skeleton::HitInter = 0.04f;

const int Skeleton::DeathParticleCount = 14;

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

		ContentsHelper::LoadSound("Sound\\Effect", "enemy_kick_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "enemy_kick_002.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "enemy_kick_003.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "enemy_die_001.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "enemy_die_002.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "enemy_die_003.wav");
		
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

	switch (GetMoveDir())
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

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		UEngineSound::SoundPlay("enemy_kick_001.wav");
		break;
	case 2:
		UEngineSound::SoundPlay("enemy_kick_002.wav");
		break;
	case 3:
		UEngineSound::SoundPlay("enemy_kick_003.wav");
		break;
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

void Skeleton::ThornHitCheck()
{
	Point CurPoint = GetLocationPoint();
	if (true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
	{
		StateChange(EHitActorState::Death);
	}
}

void Skeleton::Idle(float _DeltaTime)
{
}

void Skeleton::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.012f) }, { WinScale * IdleScale }});

	switch (GetSeeDir())
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
		if (2 < ImageRenderer->GetCurAnimationFrame() && 
			true == GetChapter()->GetTileInfoVec()[CurPoint.Y][CurPoint.X].IsThorn)
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
	CreateRandomMoveEffect();

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

	switch (GetSeeDir())
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

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		UEngineSound::SoundPlay("enemy_kick_001.wav");
		break;
	case 2:
		UEngineSound::SoundPlay("enemy_kick_002.wav");
		break;
	case 3:
		UEngineSound::SoundPlay("enemy_kick_003.wav");
		break;
	}

	CreateRandomBigHitEffect();
}

void Skeleton::Death(float _DeltaTime)
{
	DeathParticleMoveUpdate(_DeltaTime);

	if (true == AllDeathParticle.empty())
	{
		InformDestroytoChapter();
		Destroy();	
	}
}

void Skeleton::DeathStart()
{
	CreateRandomBigHitEffect();
	ImageRenderer->ActiveOff();

	for (int i = 0; i < DeathParticleCount; i++)
	{
		CreateRandomDeathParicle();
	}

	HitActorInfoUpdate(EHitActorState::Death);

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		UEngineSound::SoundPlay("enemy_die_001.wav");
		break;
	case 2:
		UEngineSound::SoundPlay("enemy_die_002.wav");
		break;
	case 3:
		UEngineSound::SoundPlay("enemy_die_003.wav");
		break;
	}
}

void Skeleton::DeathParticleMoveUpdate(float _DeltaTime)
{
	FVector WindowScale = ContentsHelper::GetWindowScale();
	std::list<DeathParticle>::iterator Iter = AllDeathParticle.begin();
	for (Iter; Iter != AllDeathParticle.end();)
	{
		if (nullptr == Iter->DeathParticleRenderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		Iter->DeathParticleMove(_DeltaTime);

		float Pos_Y = Iter->DeathParticleRenderer->GetActorBaseTransform().GetPosition().Y;
		if (WindowScale.Y * 1.5f < Pos_Y)
		{
			Iter->DeathParticleRenderer->ActiveOff();
			Iter->DeathParticleRenderer->Destroy();
			Iter = AllDeathParticle.erase(Iter);
		}
		else
		{
			++Iter;
		}
	}
}

void Skeleton::CreateRandomDeathParicle()
{
	DeathParticle NewDeathParticle = DeathParticle();
	NewDeathParticle.DeathParticleRenderer = CreateImageRenderer(RenderOrder::Effect);

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 7);
	std::string Name = "Skel_Particle_00";
	Name += RandomValue + '0';
	Name += ".png";

	FVector WinScale = ContentsHelper::GetWindowScale();
	NewDeathParticle.DeathParticleRenderer->SetImage(Name);
	NewDeathParticle.DeathParticleRenderer->SetTransform({ { 0.0f, WinScale.Y * (-0.012f)}, WinScale * DeathParticle::Scale });
	
	int SpeedX = UEngineRandom::MainRandom.RandomInt(50, 500);
	int SpeedY = UEngineRandom::MainRandom.RandomInt(-2250, -1000);
	if (1 == UEngineRandom::MainRandom.RandomInt(0, 1))
	{
		SpeedX *= -1;
	}

	NewDeathParticle.Speed = { SpeedX, SpeedY };

	AllDeathParticle.push_back(NewDeathParticle);
}

void DeathParticle::DeathParticleMove(float _DeltaTime)
{
	FVector CurPos = DeathParticleRenderer->GetPosition();
	DeathParticleRenderer->SetPosition(CurPos + (Speed * _DeltaTime));

	Speed.Y += 5000.0f * _DeltaTime;
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
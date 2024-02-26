#include "Demon.h"

#include "ContentsHelper.h"

bool Demon::IsLoad = false;
const FVector Demon::IdleScale = { 0.9f, 0.9f };
const float Demon::IdleInter = 0.065f;

const float Demon::LoveSignY_Location = 0.9f;
const float Demon::LoveSignY_MaxLocation = 1.1f;

const int Demon::StarEffectCount = 20;
FVector StarEffect::TargetPos = FVector::Zero;

const FVector Demon::LovePlosionScale = { 0.169f, 0.287f };
const float Demon::LovePlosionInter = 0.02f;

Demon::Demon()
{
}

Demon::~Demon()
{
}

void Demon::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Effect", "LoveSign.png");
		ContentsHelper::LoadImg("Effect\\Particle", "LoveStar.png");
		ContentsHelper::LoadFolder("Effect", "LovePlosion");
		IsLoad = true; 
	}

	LoveSignRenderer = AActor::CreateImageRenderer(static_cast<int>(RenderOrder::Effect));
	LoveSignRenderer->SetImage("LoveSign.png");
	LoveSignSpeed = ContentsHelper::GetTileScale().Y * 0.45f;
}

void Demon::SetDemon(std::string_view _Name, const FTransform& _FTransform)
{
	std::string AnimationName = _Name.data();
	AnimationName += "_Idle";
	ImageRenderer = CreateImageRenderer(RenderOrder::RenderActor);
	ImageRenderer->SetImage(_Name);
	ImageRenderer->SetTransform(_FTransform);
	ImageRenderer->CreateAnimation(AnimationName, _Name, 0, 11, IdleInter, true);
	StarEffect::TargetPos = ImageRenderer->GetPosition();
}

// LoveSign 상하이동 애니메이션
void Demon::LoveSignAnimation(float _DeltaTime)
{
	FVector TileScale = ContentsHelper::GetTileScale();

	if (true == IsUp)
	{
		LoveSignMove -= LoveSignSpeed * _DeltaTime;
		LoveSignRenderer->SetTransform({ { -TileScale.hX(), -(TileScale.hY() * LoveSignY_Location) + LoveSignMove }, {TileScale * LoveSignScale} });
		if (TileScale.hY() * LoveSignY_MaxLocation < (TileScale.hY() * LoveSignY_Location) - LoveSignMove)
		{
			IsUp = false;
		}
	}
	else
	{
		LoveSignMove += LoveSignSpeed * _DeltaTime;
		LoveSignRenderer->SetTransform({ { -TileScale.hX(), -(TileScale.hY() * LoveSignY_Location) + LoveSignMove }, {TileScale * LoveSignScale} });
		if (TileScale.hY() * LoveSignY_Location > (TileScale.hY() * LoveSignY_Location) - LoveSignMove)
		{
			IsUp = true;
		}
	}
}

void Demon::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	LoveSignRenderer->SetTransform({ { -TileScale.hX(), -(TileScale.hY() * LoveSignY_Location) }, {TileScale * LoveSignScale} });
	ImageRenderer->ChangeAnimation(GetName() + "_Idle");
}

void Demon::Idle(float _DeltaTime)
{
	LoveSignAnimation(_DeltaTime);
}

void Demon::VictoryStart()
{
	if (nullptr == LoveSignRenderer)
	{
		MsgBoxAssert("Renderer is nullptr");
	}

	LoveSignRenderer->ActiveOff();
	EffectCount = StarEffectCount;
	VictoryOrder = 0;
}

void Demon::Victory(float _DeltaTime)
{
	switch (VictoryOrder)
	{
	case 0:
		StarEffectUpdate(_DeltaTime);
		break;
	case 1:
		LovePlosionUpdate();
		break;
	}
}

void Demon::StarEffectUpdate(float _DeltaTime)
{
	if (1 <= EffectCount)
	{
		CreateStarEffect();
		--EffectCount;
	}

	StarEffectMoveUpdate(_DeltaTime);
}

void Demon::CreateStarEffect()
{
	float Radius = 100.0f;
	FVector Center = ImageRenderer->GetActorBaseTransform().GetPosition();

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.021f, WinScale.Y * 0.022f };
	FVector Pos = ContentsHelper::RandomCirclePoint(Center, Radius);
	Pos -= GetActorLocation();

	StarEffect Star = StarEffect();
	Star.EffectRenderer = CreateImageRenderer(RenderOrder::Effect);
	Star.EffectRenderer->SetTransform({ Pos, Scale });
	Star.EffectRenderer->SetImage("LoveStar.png");
	Star.StartPos = Star.EffectRenderer->GetPosition();
	Star.IsMove = true;
	AllStarEffect.push_back(Star);
}

void Demon::StarEffectMoveUpdate(float _DeltaTime)
{
	if (true == AllStarEffect.empty())
	{
		++VictoryOrder;
	}

	std::list<StarEffect>::iterator Iter = AllStarEffect.begin();
	for (Iter; Iter != AllStarEffect.end();)
	{
		if (nullptr == Iter->EffectRenderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		if (false == Iter->IsMove)
		{
			Iter->EffectRenderer->ActiveOff();
			Iter->EffectRenderer->Destroy();
			Iter = AllStarEffect.erase(Iter);
		}
		else
		{
			Iter->StarEffectMove(this, _DeltaTime, 0.02f);
			++Iter;
		}
	}
}

void StarEffect::StarEffectMove(const Demon* const _Demon, float _DeltaTime, float _TimeWeight)
{
	if (true == IsMove)
	{
		MoveTime += _DeltaTime + _TimeWeight;

		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		EffectRenderer->SetPosition(NextPos);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsMove = false;
		}
	}
}

void Demon::LovePlosionUpdate()
{

}

void Demon::CreateLovePlosion()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Pos = ContentsHelper::GetWindowScale();
	LovePlosionRenderer = CreateImageRenderer(RenderOrder::Effect);
	LovePlosionRenderer->SetImage("LovePlosion");
	LovePlosionRenderer->SetTransform({ { 0.0f, 0.0f }, WinScale * LovePlosionScale });
}

void Demon::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Demon::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EDemonState::Idle:
		Idle(_DeltaTime);
		break;
	case EDemonState::Victory:
		Victory(_DeltaTime);
		break;
	}
}

void Demon::StateChange(EDemonState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EDemonState::Idle:
			IdleStart();
			break;
		case EDemonState::Victory:
			VictoryStart();
			break;
		}
	}

	State = _State;
}

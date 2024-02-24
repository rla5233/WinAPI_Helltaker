#include "Demon.h"

#include "ContentsHelper.h"

bool Demon::IsLoad = false;
const FVector Demon::IdleScale = { 0.9f, 0.9f };
const float Demon::IdleInter = 0.065f;

const float Demon::LoveSignY_Location = 0.9f;
const float Demon::LoveSignY_MaxLocation = 1.1f;

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
		IsLoad = true;
	}

	LoveSignRenderer = AActor::CreateImageRenderer(static_cast<int>(RenderOrder::Effect));
	LoveSignRenderer->SetImage("LoveSign.png");
	LoveSignSpeed = ContentsHelper::GetTileScale().Y * 0.45f;
}

void Demon::SetDemon(std::string_view _Name)
{
	std::string AnimationName = _Name.data();
	AnimationName += "_Idle";
	ImageRenderer = CreateImageRenderer(RenderOrder::RenderActor);
	ImageRenderer->SetImage(_Name);
	ImageRenderer->CreateAnimation(AnimationName, _Name, 0, 11, IdleInter, true);
	StateChange(EDemonState::Idle);
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
	ImageRenderer->SetTransform({ { 0.0f, TileScale.Y * (-0.2f) }, { TileScale * IdleScale } });
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

#include "Devil.h"

#include "ContentsHelper.h"

bool Devil::IsLoad = false;

Devil::Devil()
{
}

Devil::~Devil()
{
}

void Devil::BeginPlay()
{
	RenderActor::BeginPlay();
		
	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Characters\\Chapter\\Devil", "PandeMonica");

		IsLoad = true;
	}
}

void Devil::SetDevil(std::string_view _Name)
{
	std::string AnimationName = _Name.data();
	AnimationName += "_Idle";
	CreateImageRenderer(RenderOrder::Devil);
	SetImg(_Name);
	CreateAnimation(AnimationName, _Name, 0, 11, IdleInter, true);
	StateChange(EDevilState::Idle);
}

void Devil::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ { 0, 0 }, {TileScale * IdleScale} });
	ChangeAnimation(GetName() + "_Idle");
}

void Devil::Idle(float _DeltaTime)
{}

void Devil::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Devil::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EDevilState::Idle:
		Idle(_DeltaTime);
		break;
	case EDevilState::Victory:
		break;
	}
}

void Devil::StateChange(EDevilState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EDevilState::Idle:
			IdleStart();
			break;
		case EDevilState::Victory:
			break;
		}
	}
}

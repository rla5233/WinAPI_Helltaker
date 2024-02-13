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
		ContentsHelper::LoadImg("Effect", "LoveSign.png");
		IsLoad = true;
	}

	LoveSignRenderer = AActor::CreateImageRenderer(static_cast<int>(RenderOrder::Effect));
	LoveSignRenderer->SetImage("LoveSign.png");
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

void Devil::LoveSignAnimation(float _DeltaTime)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	if (true == IsUp)
	{
		LoveSignMove -= LoveSignSpeed * _DeltaTime;
		LoveSignRenderer->SetTransform({ { -TileScale.hX(), -(TileScale.hY() * 0.45f) + LoveSignMove }, {TileScale * LoveSignScale} });
		if (TileScale.hY() * 0.65f < (TileScale.hY() * 0.45f) - LoveSignMove)
		{
			IsUp = false;
		}
	}
	else
	{
		LoveSignMove += LoveSignSpeed * _DeltaTime;
		LoveSignRenderer->SetTransform({ { -TileScale.hX(), -(TileScale.hY() * 0.45f) + LoveSignMove }, {TileScale * LoveSignScale} });
		if (TileScale.hY() * 0.45f > (TileScale.hY() * 0.45f) - LoveSignMove)
		{
			IsUp = true;
		}
	}

}

void Devil::IdleStart()
{
	FVector TileScale = ContentsHelper::GetTileScale();
	SetTransform({ { 0, 0 }, { TileScale * IdleScale }});
	LoveSignRenderer->SetTransform({ { -TileScale.hX(), - (TileScale.hY() * 0.45f) }, {TileScale * LoveSignScale}});
	ChangeAnimation(GetName() + "_Idle");
}

void Devil::Idle(float _DeltaTime)
{
	LoveSignAnimation(_DeltaTime);
}

void Devil::VictoryStart()
{
	if (nullptr == LoveSignRenderer)
	{
		MsgBoxAssert("Renderer is nullptr");
	}

	LoveSignRenderer->Destroy();
}

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
			VictoryStart();
			break;
		}
	}

	State = _State;
}

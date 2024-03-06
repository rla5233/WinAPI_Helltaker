#include "Sin_Demon.h"

bool Sin_Demon::IsLoad = false;

const FVector Sin_Demon::Scale = { 0.0521f, 0.093f };
const FVector Sin_Demon::AppearScale = { 0.0521f, 0.241f };
const float Sin_Demon::AppearInter = 0.065f;

Sin_Demon::Sin_Demon()
{
}

Sin_Demon::~Sin_Demon()
{
}

void Sin_Demon::BeginPlay()
{
	Demon::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadFolder("Chapter\\Demon", "Judge_Jump");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Judge");

		IsLoad = true;
	}
}

void Sin_Demon::SetDemon(std::string_view _Name, const FTransform& _FTransform)
{
	std::string AnimationName = _Name.data();
	AnimationName += "_Idle";
	ImageRenderer = CreateImageRenderer(SinRenderOrder::Top);
	ImageRenderer->SetImage(_Name);
	ImageRenderer->SetTransform(_FTransform);
	ImageRenderer->CreateAnimation(AnimationName, _Name, 0, 11, IdleInter, true);
	StarEffect::TargetPos = ImageRenderer->GetPosition();
}

void Sin_Demon::Tick(float _DeltaTime)
{
	Demon::Tick(_DeltaTime);
}

void Sin_Demon::Sin_AppearStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImageRenderer->CreateAnimation("Judge_Appear", "Judge_Jump", 0, 8, IdleInter, false);
	ImageRenderer->SetTransform({ { 0.0f, 0.0f }, WinScale * AppearScale });
}

void Sin_Demon::Sin_Appear(float _DeltaTime)
{
	int a = 0;
}

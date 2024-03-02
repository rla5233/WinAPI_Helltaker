#include "SinComponent.h"

SinComponent::SinComponent()
{
}

SinComponent::~SinComponent()
{
}

void SinComponent::CreateImageRenderer(std::string_view _KeyName, SinRenderOrder _Order)
{
	UImageRenderer* Renderer = RenderActor::CreateImageRenderer(_Order);
	ImageRenderers.insert({ _KeyName.data(), Renderer});
}

void SinComponent::MoveY_Update(float _Speed, float _DeltaTime)
{
	if (true == IsMove)
	{
		AddActorLocation({ 0.0f, _Speed * _DeltaTime });

		if (EndPosY >= GetActorLocation().Y)
		{
			float Diff = GetActorLocation().Y - EndPosY;
			SetActorLocation({ GetActorLocation().X, ResetPosY + Diff });
		}
	}
}
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

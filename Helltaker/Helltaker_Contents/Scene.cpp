#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::CreateImageRenderer(RenderOrder _Order)
{
	ImageRenderer = RenderActor::CreateImageRenderer(_Order);
}

bool Scene::FadeInUpdate(float _DeltaTime, float _TimeWeight /* = 1.0f*/)
{
	if (false == IsFadeIn)
	{
		return false;
	}

	if (true == IsFadeIn)
	{
		TimeCount += _DeltaTime * _TimeWeight;
		float NextAlpha = ContentsHelper::LerpClampf(0, 255, TimeCount);
		ImageRenderer->SetAlpha(NextAlpha);

		if (1.0f <= TimeCount)
		{
			TimeCount = 0.0f;
			IsFadeIn = false;
		}
	}

	return true;
}

bool Scene::FadeOutUpdate(float _DeltaTime, float _TimeWeight /* = 1.0f*/)
{
	return false
}

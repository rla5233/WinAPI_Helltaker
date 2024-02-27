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
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::CreateImageRenderer(RenderOrder _Order)
{
	Renderer = RenderActor::CreateImageRenderer(_Order);
}
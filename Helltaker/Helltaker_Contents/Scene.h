#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Scene : public RenderActor
{
public:
	// constructor destructor
	Scene();
	~Scene();

	// delete Function
	Scene(const Scene& _Other) = delete;
	Scene(Scene&& _Other) noexcept = delete;
	Scene& operator=(const Scene& _Other) = delete;
	Scene& operator=(Scene&& _Other) noexcept = delete;

	void CreateImageRenderer(RenderOrder _Order);

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
};

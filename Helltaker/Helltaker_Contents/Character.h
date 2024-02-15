#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Character : public RenderActor
{
public:
	// constructor destructor
	Character();
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	void CreateImageRenderer(RenderOrder _Order);
	void CreateNameRenderer(RenderOrder _Order);

	UImageRenderer* GetImageRenderer()
	{
		return ImageRenderer;
	}

	UImageRenderer* GetNameRenderer()
	{
		return NameRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* NameRenderer = nullptr;
};

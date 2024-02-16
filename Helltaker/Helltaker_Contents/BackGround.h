#pragma once

#include "RenderActor.h"

// Ό³Έν :
class BackGround : public RenderActor
{
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void CreateBackGround(std::string_view _Name);
	void BackGroundChange(std::string_view _Name);

	UImageRenderer* GetImageRenderer()
	{
		return ImageRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
};

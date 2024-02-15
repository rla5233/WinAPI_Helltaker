#pragma once

#include "RenderActor.h"

// Ό³Έν :
class UI : public RenderActor
{
public:
	// constructor destructor
	UI();
	~UI();

	// delete Function
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;
	
	void CreateImageRenderer(RenderOrder _Order);
	void CreateTextRenderer(RenderOrder _Order);

	UImageRenderer* GetImageRenderer()
	{
		return ImageRenderer;
	}

	UImageRenderer* GetTextRenderer()
	{
		return TextRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* TextRenderer = nullptr;
};

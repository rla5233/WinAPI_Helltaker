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
	
	void CreateImageRenderer(SinRenderOrder _Order);
	void CreateImageRenderer(RenderOrder _Order);
	void CreateTextRenderer(SinRenderOrder _Order);
	void CreateTextRenderer(RenderOrder _Order);

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	UImageRenderer* GetTextRenderer() const 
	{
		return TextRenderer;
	}

protected:

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* TextRenderer = nullptr;
};

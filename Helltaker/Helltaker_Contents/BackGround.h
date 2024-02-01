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
	
	void LoadRenderImage(std::string_view _Name) override;
	void SetRenderImage(std::string_view _Name) override;
	
protected:

private:

};

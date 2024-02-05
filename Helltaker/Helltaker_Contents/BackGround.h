#pragma once

#include <EngineCore/Actor.h>
#include "ContentsEnum.h"


// Ό³Έν :
class BackGround : public AActor
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
	
	void LoadRenderImage(std::string_view _Path, std::string_view _Name);
	
	void SetRenderImage(std::string_view _Name, int _Order);
	void SetRenderImage(std::string_view _Name, RenderOrder _Order);
	
protected:

private:
	UImageRenderer* Renderer = nullptr;

};

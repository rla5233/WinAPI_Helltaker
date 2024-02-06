#pragma once

#include "ContentsHelper.h"

#include <EngineBase/Transform.h>
#include <EngineCore/Actor.h>


// Ό³Έν :
class RenderActor : public AActor
{
public:
	// constructor destructor
	RenderActor();
	~RenderActor();
	
	// delete Function
	RenderActor(const RenderActor& _Other) = delete;
	RenderActor(RenderActor&& _Other) noexcept = delete;
	RenderActor& operator=(const RenderActor& _Other) = delete;
	RenderActor& operator=(RenderActor&& _Other) noexcept = delete;

	void LoadFolder(std::string_view _Path);
	void LoadImg(std::string_view _Path);

	void SetImg(std::string_view _Name);
	void SetTransform(const FTransform& _Value);

	void CreateImageRenderer(RenderOrder _Order);
	void CreateImageRenderer(int _Order);

	FVector GetRendererImageScale();


protected:
	UImageRenderer* Renderer = nullptr;

private:
};


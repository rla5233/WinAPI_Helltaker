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
	void LoadImg(std::string_view _Path, std::string_view _Name);

	//void SetImg(std::string_view _Name);
	//void SetTransform(const FTransform& _Value);

	UImageRenderer* CreateImageRenderer(RenderOrder _Order);

	//void CreateAnimation(
	//	std::string_view _AnimationName,
	//	std::string_view _ImageName,
	//	int _Start,
	//	int _End,
	//	float _Inter,
	//	bool _Loop = true
	//);

	//void ChangeAnimation(std::string_view _AnimationName);
	//void AnimationReset();

	//FVector GetRendererImageScale();

	//void RenderActiveOn();
	//void RenderActiveOff();

protected:
	
private:

};


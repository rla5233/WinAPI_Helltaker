#pragma once
#include "ContentsHelper.h"

#include <EngineBase/Transform.h>
#include <EngineCore/Actor.h>

class ChapterManager;

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

	ChapterManager* GetChapter();

	UImageRenderer* CreateImageRenderer(RenderOrder _Order);

	void VibrationEffect(UImageRenderer* _Renderer);

protected:
	
private:

};


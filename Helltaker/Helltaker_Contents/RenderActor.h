#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class RenderActor : virtual public AActor
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

	virtual void LoadRenderImage(std::string_view _Name) {};
	virtual void SetRenderImage(std::string_view _Name) {};
	void LoadAndSetRenderImage(std::string_view _Name);

protected:
	UImageRenderer* Renderer = nullptr;

private:

};

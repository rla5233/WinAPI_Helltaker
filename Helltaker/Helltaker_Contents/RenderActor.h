#pragma once

// Ό³Έν :
class RenderActor
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

protected:

private:

};

#pragma once

#include "RenderActor.h"

// 수정 (클래스 삭제 가능?)

// 설명 :
class Dialogue : public RenderActor
{
public:
	// constructor destructor
	Dialogue();
	~Dialogue();

	// delete Function
	Dialogue(const Dialogue& _Other) = delete;
	Dialogue(Dialogue&& _Other) noexcept = delete;
	Dialogue& operator=(const Dialogue& _Other) = delete;
	Dialogue& operator=(Dialogue&& _Other) noexcept = delete;

	void CreateImageRenderer(RenderOrder _Order);

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:

private:
	UImageRenderer* Renderer = nullptr;
};

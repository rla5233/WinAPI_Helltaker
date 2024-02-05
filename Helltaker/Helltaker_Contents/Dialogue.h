#pragma once

#include "ContentsEnum.h"

#include <EngineCore/Actor.h>

// Ό³Έν :
class Dialogue : public AActor
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

	void LoadRenderImage(std::string_view _Path, std::string_view _Name);

	void SetRenderImage(std::string_view _Name, int _Order);
	void SetRenderImage(std::string_view _Name, RenderOrder _Order);

protected:

private:
	UImageRenderer* Renderer = nullptr;
};

#pragma once

#include "ContentsEnum.h"

#include <EngineCore/Actor.h>

// ���� :
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



protected:
	void BeginPlay() override;

private:
	UImageRenderer* Renderer = nullptr;
};

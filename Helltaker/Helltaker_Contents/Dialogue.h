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

	void LoadFolderDialogue();
	void SetFolderDialogue();

	void LoadImgDialogue();
	void SetImgDialogue();

	void SetScale(const FVector& _Scale)
	{
		Scale = _Scale;
	}

protected:

private:
	UImageRenderer* Renderer = nullptr;
	FVector Scale = FVector::Zero;

};

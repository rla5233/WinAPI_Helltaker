#pragma once

#include "ContentsEnum.h"

#include <EngineCore/Actor.h>
#include <EngineBase/EngineDebug.h>

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
	void SetImgDialogue(bool _SetOrgScale);

	void SetScale(const FVector& _Scale)
	{
		Scale = _Scale;
	}

	FVector GetImgScale()
	{
		if (nullptr != Renderer)
		{
			MsgBoxAssert("Dialogue Renderer is nullptr");
		}

		return Renderer->GetImage()->GetScale();
	}

protected:

private:
	UImageRenderer* Renderer = nullptr;
	FVector Scale = FVector::Zero;

};

#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class Character : public AActor
{
public:
	// constructor destructor
	Character();
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	void LoadFolder();
	void SetFolder();

	void LoadImg();
	void SetImg(bool _SetOrgScale);

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

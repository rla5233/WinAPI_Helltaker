#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class UI : public AActor
{
public:
	// constructor destructor
	UI();
	~UI();

	// delete Function
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;

	void LoadFolder();
	void LoadImg();

	void SetImg(bool _SetOrgScale);

	void SetScale(const FVector& _Scale)
	{
		Scale = _Scale;
	}

	void CreateUIAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool _Loop = true
	);

	void ChangeUIAnimation(std::string_view _AnimationName);

	FVector GetImgScale()
	{
		if (nullptr != Renderer)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		return Renderer->GetImage()->GetScale();
	}

protected:

private:
	UImageRenderer* Renderer = nullptr;
	FVector Scale = FVector::Zero;

};

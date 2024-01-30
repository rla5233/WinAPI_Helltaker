#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

class UWindowImage;
// 설명 :
class UImageRenderer : public USceneComponent
{
public:
	// constrcuter destructer
	UImageRenderer();
	~UImageRenderer();

	// delete Function
	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);
	// 이미지를 세팅하는 역할만 하고
	void SetImage(std::string_view _Name, bool _IsImageScale = false);

	// 이미지를 세팅하면서 이미지의 크기로 랜더러의 스케일을 변경하는것도 함께하는 함수
	void SetImageToScale(std::string_view _Name);

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image;
};


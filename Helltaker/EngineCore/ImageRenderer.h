#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>
#include <map>

enum class EImageSortType
{
	Center,
	Left,
	Right,
};

class UAnimationInfo
{
public:
	// 애니메이션을 구성할때 이미지는 1장
	UWindowImage* Image = nullptr;
	std::string Name;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;
	bool IsEnd = false;
	std::vector<float> Times;
	std::vector<int> Indexs;

	int Update(float _DeltaTime);
};

class AActor;
class UWindowImage;
// 설명 :
class UImageRenderer : public USceneComponent
{
public:
	friend AActor;

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
	void SetImage(std::string_view _Name, int _InfoIndex = 0);

	bool IsAnimation(std::string_view _Name);

	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}

	int GetImageIndex()
	{
		return InfoIndex;
	}

	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool _Loop = true
	);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		std::vector<int> _Indexs,
		float _Inter,
		bool _Loop = true
	);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		std::vector<int> _Indexs,
		std::vector<float> _Inters,
		bool _Loop = true
	);


	void ChangeAnimation(std::string_view _AnimationName, bool _IsForce = false, int _StartIndex = 0, float _Time = -1.0f);
	void AnimationReset();

	void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	void SetTransColor(Color8Bit _Color)
	{
		TransColor = _Color;
	}

	// 0~1.0f
	void SetAlpha(float _Alpha)
	{
		if (0.0f >= _Alpha)
		{
			_Alpha = 0.0f;
		}

		if (1.0f <= _Alpha)
		{
			_Alpha = 1.0f;
		}

		TransColor.A = static_cast<char>(_Alpha * 255.0f);
	}

	UWindowImage* GetImage() const
	{
		return Image;
	}

	void CameraEffectOff()
	{
		CameraEffect = false;
	}

	bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
	}

	int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	int GetCurAnimationImageFrame() const
	{
		const std::vector<int>& Indexs = CurAnimation->Indexs;
		return Indexs[CurAnimation->CurFrame];
	}

	float GetCurAnimationTime() const
	{
		return CurAnimation->CurTime;
	}

	UAnimationInfo* GetCurAnimation() const
	{
		return CurAnimation;
	}

	void TextRender(float _DeltaTime);
	void ImageRender(float _DeltaTime);

	void SetText(std::string_view _Text)
	{
		Text = _Text;
	}
	void SetFont(std::string_view _Font)
	{
		Font = _Font;
	}
	void SetTextSize(float _Value)
	{
		Size = _Value;
	}
	void SetTextColor(Color8Bit _Color, Color8Bit _Color2 = Color8Bit::White)  //변경
	{
		TextColor = _Color;
		TextColor2 = _Color2; //추가
	}
	void SetCameraRatio(float _Ratio)
	{
		CameraRatio = _Ratio;
	}

	FTransform GetRenderTransForm();

	// Text 효과
	void SetTextEffect(int _Effect = 0)
	{
		TextEffect = _Effect;
	}

	void SetTextSortOption(Gdiplus::StringAlignment _SortOption1, Gdiplus::StringAlignment _SortOption2)
	{
		SortOption1 = _SortOption1;
		SortOption2 = _SortOption2;
	}

	void SetSortType(EImageSortType _SortType)
	{
		SortType = _SortType;
	}

	void AutoImageScale(float _AutoScale = 1.0f)
	{
		AutoImageScaleValue = true;
		AutoImageScaleRatio = _AutoScale;
	}

protected:
	void BeginPlay() override;
	void Tick(float _Time) override;

private:
	int InfoIndex = 0;
	UWindowImage* Image = nullptr;
	FTransform ImageCuttingTransform;
	Color8Bit TransColor;

	bool CameraEffect = true;
	float CameraRatio = 1.0f;

	std::map<std::string, UAnimationInfo> AnimationInfos;
	UAnimationInfo* CurAnimation = nullptr;

	// 회전
	float Angle = 0.0f;

	std::string Text = "";
	std::string Font = "궁서";
	float Size = 10.0f;
	Color8Bit TextColor = Color8Bit::BlackA;
	Color8Bit TextColor2 = Color8Bit::BlackA; //추가
	int TextEffect = 0;

	bool AutoImageScaleValue = false;
	float AutoImageScaleRatio = 1.0f;

	EImageSortType SortType = EImageSortType::Center;

	Gdiplus::StringAlignment SortOption1 = Gdiplus::StringAlignment::StringAlignmentCenter;
	Gdiplus::StringAlignment SortOption2 = Gdiplus::StringAlignment::StringAlignmentCenter;

	// Default : 0, 
	// Bold & Italic : 1, (custom)
	// Bold : 2,
	// ...
};


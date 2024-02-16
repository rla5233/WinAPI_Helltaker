#pragma once

#include "RenderActor.h"

// ���� :
class Text : public RenderActor
{
public:
	// constructor destructor
	Text();
	~Text();

	// delete Function
	Text(const Text& _Other) = delete;
	Text(Text&& _Other) noexcept = delete;
	Text& operator=(const Text& _Other) = delete;
	Text& operator=(Text&& _Other) noexcept = delete;

	void TextSetting(float _Size, Color8Bit _Color, std::string_view _Font = "���� ����");
	void SetTransForm(FTransform _FTransform);
	void SetText(std::string_view _Text);

	void CreateTextRenderer(RenderOrder _Order);

protected:

private:
	UImageRenderer* TextRenderer = nullptr;
};

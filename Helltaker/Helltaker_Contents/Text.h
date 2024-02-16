#pragma once

#include "RenderActor.h"

// ¼³¸í :
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

	void TextSetting(std::string_view _Font = "¸¼Àº °íµñ", int _Size, Color8Bit _Color);
	void SetTransForm(FTransform _FTransform);
	void SetText(std::string_view _Text);

	void CreateTextRenderer(RenderOrder _Order);

protected:

private:
	UImageRenderer* TextRenderer = nullptr;
};

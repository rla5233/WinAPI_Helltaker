#include "Text.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::CreateTextRenderer(RenderOrder _Order)
{
	TextRenderer = CreateImageRenderer(_Order);
}



void Text::TextSetting(std::string_view _Font, int _Size, Color8Bit _Color)
{
	TextRenderer->SetFont(_Font);
	TextRenderer->SetTextSize(_Size);
	TextRenderer->SetTextColor(_Color);
}

void Text::SetTransForm(FTransform _FTransform)
{
	TextRenderer->SetTransform(_FTransform);
}

void Text::SetText(std::string_view _Text)
{
	TextRenderer->SetText(_Text);
}
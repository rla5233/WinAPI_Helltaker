#include "EngineDebug.h"
#include <vector>
#include <EnginePlatform\WindowImage.h>

namespace UEngineDebug
{
	struct TextOutData
	{
	public:
		std::string Text;
		float _Size = 20.0f;
	};

	std::vector<TextOutData> PrintText;

	void DebugTextPrint(std::string_view _Text, float _Size)
	{
		PrintText.push_back(TextOutData{ _Text.data(), _Size });
	}



	void PrintDebugText(UWindowImage* _Image)
	{
		Gdiplus::StringFormat stringFormat;
		stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
		FTransform Trans;
		Color8Bit Color = Color8Bit::Red;

		for (int i = 0; i < static_cast<int>(PrintText.size()); i++)
		{
			TextOutData& Data = PrintText[i];
			_Image->TextCopyFormat(Data.Text, "±Ã¼­", stringFormat, Data._Size, Trans, Color);
			Trans.AddPosition({ 0.0f, Data._Size });
		}

		PrintText.clear();
	}

}
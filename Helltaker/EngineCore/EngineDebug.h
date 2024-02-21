#pragma once
#include <EngineBase\EngineDebug.h>
#include <EnginePlatform\EngineWindow.h>

#include <string>
#include <string_view>

namespace UEngineDebug
{
	void DebugTextPrint(std::string_view _Text, float _Size);
	void PrintDebugText(UWindowImage* _Image);

}